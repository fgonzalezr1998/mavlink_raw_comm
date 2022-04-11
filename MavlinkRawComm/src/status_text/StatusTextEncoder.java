package status_text;

public class StatusTextEncoder {

    public static byte CRCEXTRA = 83 & 0xFF;    // without sign

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

    private static final int MAXTEXTLENGTH = 50;
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
        int len = MAXTEXTLENGTH + 1;
        byte[] outDigest = new byte[len];

        if (severity < StatusSeverity.EMERGENGY || severity > StatusSeverity.DEBUG) {
            throw new StatusTextPayloadEx("Severity Incorrect");
        }
        if (msg.length() > MAXTEXTLENGTH) {
            throw new StatusTextPayloadEx("Message too long");
        }

        // Field1 severity
        byte sev = (byte)severity;

        //Field2 text as char array
        byte[] text = new byte[MAXTEXTLENGTH];
        byte[] msgBytes;

        msgBytes = msg.getBytes();
        // copy into text:
        int i;
        for (i = 0; i < msgBytes.length; i++) {
            text[i] = (byte)(msgBytes[i] & 0xFF);
        }
        // Fill with zeros:
        for (i = msgBytes.length; i < MAXTEXTLENGTH; i++) {
            text[i] = (byte)(0x00 & 0xFF);
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
        digest[0] = (byte)(0xFE & 0xFF);

        // Field2 Payload length
        digest[1] = (byte)(len_payload & 0xFF);

        //Field3 Seq number
        digest[2] = (byte)(seq_n & 0xFF);

        //Field4 System ID
        digest[3] = (byte)(sys_id & 0xFF);

        //Field5 Component ID
        digest[4] = (byte)(comp_id & 0xFF);

        //Field6 Message ID
        digest[5] = (byte)(MSGID & 0xFF);

        return digest;
    }
}
