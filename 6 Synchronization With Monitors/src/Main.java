import java.util.Random;

public class Main {
  public static void main(String[] args) {
    BoundedBuffer buffer = new BoundedBuffer(10);

    final int totalStrings = 90;
    int remainingStrings = totalStrings;
    for (int i = 0; i < 3; i++) {
      new Thread(new Runnable() {
        @Override
        public void run() {
          try {
            Random random = new Random();
            int threadId = (int) Thread.currentThread().getId();
            for (int j = 0; j < 30; j++) {
              int randomNumber = random.nextInt(90000) + 10000;
              String data = threadId + "-" + randomNumber;
              buffer.deposit(data);
              System.out.println("Thread " + threadId + " deposited " + data);
            }
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
      }).start();
    }

    try {
      Thread.sleep(5000);
    } catch (InterruptedException e) {
      e.printStackTrace();
    }

    while (true) {
      try {
        String data = buffer.fetch();
        System.out.println("Fetched " + data);
      } catch (InterruptedException e) {
        System.out.println("Program execution done");
        e.printStackTrace();
      }

      if (--remainingStrings == 0) {
        System.out.println("Execution complete");
        break;
      }

    }
  }
}
