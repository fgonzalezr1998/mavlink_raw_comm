import mavlink_encoder.MavlinkEncoder;
import status_text.StatusTextEncoder;
import status_text.StatusTextPayloadEx;

public class Main {

    private void printDigest(byte[] digest) {
        for (int i = 0; i < digest.length; i++) {
            System.out.print(String.format("%02x", digest[i]));
        }
        System.out.print("\n");
    }


    public void initialize() {
        MavlinkEncoder encoder = new MavlinkEncoder(1, 0);
        encoder.setSeqN(140);
        try {
            byte[] msg = encoder.statusTextMsg("Hello", StatusTextEncoder.StatusSeverity.INFO);
            printDigest(msg);
            MavlinkEncoder.DigestMsg decoded = encoder.decodePkg(msg);
            if (decoded != null) {
                printDigest(decoded.header);
                printDigest(decoded.payload);
                System.out.println(decoded.checksum);
                System.out.println(decoded.msg_type & 0xff);
            }
        } catch (StatusTextPayloadEx e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        Main init = new Main();
        init.initialize();
    }
}
