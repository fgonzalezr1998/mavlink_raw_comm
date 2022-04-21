package mavlink_encoder;

import status_text.StatusTextEncoder;
import status_text.StatusTextPayloadEx;

import java.sql.Array;
import java.util.Arrays;

public class MavlinkEncoder {

    public static class MsgsIds {
        public static final int StatusText = 253;
    }

    public static class DigestMsg {
        public int msg_type;
        public byte[] header;
        public byte[] payload;
        public int checksum;
    }

    private static final int MinPkgLen = 8;
    private int seq_n = 0;
    private int sys_id, comp_id;
    public  MavlinkEncoder(int sys_id, int comp_id) {
        this.seq_n = 0;
        this.sys_id = sys_id;
        this.comp_id = comp_id;
        System.out.println("I'm Mavlink Encoder");
    }

    /**Returns a digest with full statustext message encoded following mavlink
     * packages specification
     *
     * @param msg Message to be sent (50 chars maximum)
     * @param severity Severity of the statustext message
     * @return Byte array that contains the full message encoded and ready
     *  to be sent to a Pixhawk/Autopilot
     * @throws StatusTextPayloadEx Thrown if the message is larger than 50 bytes
     */
    public byte[] statusTextMsg(String msg, int severity) throws StatusTextPayloadEx {
        byte[] payloadDigest, headerDigest, bodyPkg, checksum;
        StatusTextEncoder textEncoder = StatusTextEncoder.getInstance();

        // Compose Payload
        payloadDigest = textEncoder.composePayload(msg, severity);

        // Compose Header
        headerDigest = textEncoder.composeHeader(payloadDigest.length, seq_n, sys_id, comp_id);

        // Concatenate Header + Payload
        bodyPkg = concatenateDigests(headerDigest, payloadDigest);

        // Calculate checksum
        int check = checksum(Arrays.copyOfRange(bodyPkg, 1, bodyPkg.length), StatusTextEncoder.CRCEXTRA);

        checksum = new byte[2];
        checksum[0] = (byte) (check & 0xFF);
        checksum[1] = (byte) ((check >> 8) & 0xFF);

        return concatenateDigests(bodyPkg, checksum);
    }

    public DigestMsg decodePkg(byte[] digest) {
        DigestMsg digestMsg = null;
        if (msgIntegrityIsOk(digest)) {
            digestMsg = new DigestMsg();

            // Get header
            digestMsg.header = new byte[MinPkgLen - 2];
            for (int i = 0; i < MinPkgLen - 2; i++) {
                digestMsg.header[i] = digest[i];
            }

            // Get payload
            digestMsg.payload = new byte[digest.length - MinPkgLen];
            int j = 0;
            for (int i = MinPkgLen - 2; i < digest.length - 2; i++) {
                digestMsg.payload[j++] = digest[i];
            }

            // Get Checksum
            digestMsg.checksum = ((digest[digest.length - 1] & 0xff) << 8) | (digest[digest.length - 2] & 0xff);

            // Get message id
            digestMsg.msg_type = digest[MinPkgLen - 3] & 0xff;
        }

        return digestMsg;
    }

    /**
     * Returns if the codified mavlink message is correctly built. It checks the checksum
     * respecting to the package data
     *
     * @param full_pkg mavlink message
     * @return boolean indicating the integrity of the message
     */
    public boolean msgIntegrityIsOk(byte[] full_pkg) {
        byte crc_extra;
        int msg_id;

        msg_id = full_pkg[MinPkgLen - 3] & 0xFF;
        crc_extra = crcExtra(msg_id);

        return crcIsOk(full_pkg, crc_extra);
    }

    public byte crcExtra(int msg_id) {
        byte crc_extra;
        switch (msg_id) {
            case MsgsIds.StatusText:
                crc_extra = StatusTextEncoder.CRCEXTRA;
                break;
            default:
                crc_extra = 0x00 & 0xFF;
        }
        return crc_extra;
    }

    /**
     * Increase in one the sequence number. It will be encoded in the next package bytes calculated
     */
    public void increaseSeqN() {
        seq_n++;
    }

    /**Set a specific Sequence Number. It will be encoded in the next package bytes calculated
     *
     * @param seq_n Sequence number to set
     */
    public void setSeqN(int seq_n) {
        this.seq_n = seq_n;
    }

    /**
     *
     * @param digest Mavlink message to check its crc (checksum)
     * @param crc_extra crc extra corresponding to the type of message
     * @return true if crc is ok. Else, false is returned
     */
    private boolean crcIsOk(byte[] digest, byte crc_extra) {
        // Calculate the checksum of the message excluding the crc
        int msg_checksum = checksum(Arrays.copyOfRange(digest, 1, digest.length - 2), crc_extra);

        // Get checksum encoded in the package
        int pkg_checksum = ((digest[digest.length - 1] & 0xff) << 8) | (digest[digest.length - 2] & 0xff);

        return msg_checksum == pkg_checksum;
    }

    /**
     * Calculate a checksum from mavlink digest message
     *
     * @param buffer Digest to calculate the checksum
     * @param crc_extra crc extra corresponding to the type of message
     * @return the calculated checksum (integer)
     */
    private int checksum(byte[] buffer, byte crc_extra) {
        Checksum checksumComposer = new Checksum();
        checksumComposer.crcCalculate(buffer);
        checksumComposer.crcAccumulate(crc_extra);
        return checksumComposer.getCrc();
    }

    private byte[] concatenateDigests(byte[] digest1, byte[] digest2) {
        byte[] out = new byte[digest1.length + digest2.length];
        int i;

        for (i = 0; i < digest1.length; i++) {
            out[i] = digest1[i];
        }
        for (i = 0; i < digest2.length; i++) {
            out[digest1.length + i] = digest2[i];
        }

        return out;
    }
}
