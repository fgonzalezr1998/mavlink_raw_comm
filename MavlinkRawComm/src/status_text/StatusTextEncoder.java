package status_text;

public class StatusTextEncoder {
    public class StatusSeverity {
        public static final int EMERGENGY = 0;
        public static final int ALERT = 1;
        public static final int CRITICAL = 2;
        public static final int ERROR = 3;
        public static final int WARNING = 4;
        public static final int NOTICE = 5;
        public static final int INFO = 6;
        public static final int DEBUG = 7;
    }

    private static final int MAXTEXTLENGHT = 50;
    private static final int MINPKGLEN = 8;
    private static final int MSGID = 253;

    private static StatusTextEncoder statusTextEncoder = null;

    private StatusTextEncoder() {}

    public static StatusTextEncoder getInstance() {
        if (statusTextEncoder == null)
            statusTextEncoder = new StatusTextEncoder();
        return statusTextEncoder;
    }

    public byte[] composePayload(String msg, int severity) {
        int len = MAXTEXTLENGHT + 1;
        byte[] outDigest = new byte[len];

        if (severity < StatusSeverity.EMERGENGY || severity > StatusSeverity.DEBUG) {
            throw new StatusTextPayloadEx("Severity Incorrect");
        }
        if (msg.length() > MAXTEXTLENGHT) {
            throw new StatusTextPayloadEx("Message too long");
        }

        // Field1 severity
        byte sev = (byte)severity;

        //Field2 text as char array
        byte[] text = new byte[MAXTEXTLENGHT];
        byte[] msgBytes;

        msgBytes = msg.getBytes();
        // copy into text:
        int i;
        for (i = 0; i < msgBytes.length; i++) {
            text[i] = msgBytes[i];
        }
        // Fill with zeros:
        for (i = msgBytes.length; i < MAXTEXTLENGHT; i++) {
            text[i] = (byte)0x00;
        }

        // Concatenate all fields
        outDigest[0] = sev;
        for (i = 1; i < len; i++) {
            outDigest[i] = text[i - 1];
        }

        return outDigest;
    }

    public byte[] composeHeader(int len_payload, int seq_n, int sys_id, int comp_id) {
        int len = MINPKGLEN - 2;
        byte[] digest = new byte[len];

        // Field1 Package start marker
        digest[0] = (byte)0xFE;

        // Field2 Payload length
        digest[1] = (byte)len_payload;

        //Field3 Seq number
        digest[2] = (byte)seq_n;

        //Field4 System ID
        digest[3] = (byte)sys_id;

        //Field5 Component ID
        digest[4] = (byte)comp_id;

        //Field6 Message ID
        digest[5] = (byte)MSGID;

        return digest;
    }
}
