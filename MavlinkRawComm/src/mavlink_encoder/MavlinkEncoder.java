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
        byte[] payloadDigest;
        StatusTextEncoder textEncoder = StatusTextEncoder.getInstance();

        // Compose the payload
        payloadDigest = textEncoder.composePayload(msg, severity);

        return payloadDigest;
    }
}
