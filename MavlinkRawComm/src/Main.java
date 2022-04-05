import mavlink_encoder.MavlinkEncoder;
import status_text.StatusTextEncoder;
import status_text.StatusTextPayloadEx;

public class Main {

    public void initialize() {
        MavlinkEncoder encoder = new MavlinkEncoder(1, 0);
        try {
            encoder.statusTextMsg("Hello", StatusTextEncoder.StatusSeverity.INFO);
        } catch (StatusTextPayloadEx e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        Main init = new Main();
        init.initialize();
    }
}
