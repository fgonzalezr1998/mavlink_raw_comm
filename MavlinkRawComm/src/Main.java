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
            System.out.println("Coding 'Hello World' text...");
            byte[] msg = encoder.statusTextMsg("Hello World!", StatusTextEncoder.StatusSeverity.INFO);

            System.out.print("Digest:\n\t");
            printDigest(msg);
            System.out.println("Decoding previous message...");
            MavlinkEncoder.DigestMsg decoded = encoder.decodePkg(msg);
            if (decoded != null) {
                System.out.print("Header:\n\t");
                printDigest(decoded.header);

                System.out.print("Payload:\n\t");
                printDigest(decoded.payload);

                System.out.print("Checksum:\n\t");
                System.out.println(decoded.checksum);

                System.out.print("Type of Message:\n\t");
                System.out.println(decoded.msg_type);

                if (decoded.msg_type == MavlinkEncoder.MsgsIds.StatusText) {
                    System.out.println("Decoding Payload...");
                    StatusTextEncoder textEncoder = StatusTextEncoder.getInstance();
                    StatusTextEncoder.PayloadStatusText payloadStatusText;
                    payloadStatusText = textEncoder.decodePayload(decoded.payload);

                    System.out.print("Severity:\n\t");
                    System.out.println(payloadStatusText.getSeverity());
                    System.out.print("Text:\n\t");
                    System.out.println(payloadStatusText.getText());
                }
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
