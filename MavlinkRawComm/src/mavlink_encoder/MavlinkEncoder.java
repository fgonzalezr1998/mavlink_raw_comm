package mavlink_encoder;

import status_text.StatusTextEncoder;
import status_text.StatusTextPayloadEx;

public class MavlinkEncoder {
    private int seq_n = 0;
    private int sys_id, comp_id;
    public  MavlinkEncoder(int sys_id, int comp_id) {
        this.seq_n = 0;
        this.sys_id = sys_id;
        this.comp_id = comp_id;
        System.out.println("I'm Mavlink Encoder");
    }

    public byte[] statusTextMsg(String msg, int severity) throws StatusTextPayloadEx {
        byte[] payloadDigest, headerDigest, bodyPkg;
        StatusTextEncoder textEncoder = StatusTextEncoder.getInstance();

        // Compose Payload
        payloadDigest = textEncoder.composePayload(msg, severity);

        // Compose Header
        headerDigest = textEncoder.composeHeader(payloadDigest.length, seq_n, sys_id, comp_id);

        // Concatenate Header + Payload
        bodyPkg = concatenateDigests(headerDigest, payloadDigest);

        // Calculate checksum

        return bodyPkg;
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
