package mavlink_encoder;

public class Checksum {
    private static final int X25_INIT_CRC = 0xFFFF;

    private char crcAccum;  // unsigned int 16 bytes

    public Checksum() {
        crcInit();
    }

    public void crcInit() {
        this.crcAccum = X25_INIT_CRC;
    }

    public void crcAccumulate(byte data) {
        char tmp;

        tmp = (char)(data ^ (byte)(crcAccum & 0xFF));
        tmp = (char)(tmp & 0xFF);   // delete the sign

        tmp ^= (tmp << 4);
        tmp = (char)(tmp & 0xFF);   // delete the sign

        crcAccum = (char)((crcAccum >>> 8) ^ (tmp << 8) ^ (tmp << 3) ^ (tmp >>> 4));
    }

    public void crcCalculate(byte[] buffer) {
        crcInit();
        for (int i = 0 ; i < buffer.length; i++) {
            crcAccumulate(buffer[i]);
        }
    }

    public int getCrc() {
        return crcAccum;
    }
}
