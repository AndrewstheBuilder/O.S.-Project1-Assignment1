public class Consumer extends Thread {
    int[] sharedBuffer;
    int currLoc;

    Consumer(int[] sharedBuffer, int currLoc){
        this.sharedBuffer = sharedBuffer;
        this.currLoc = currLoc;
    }

    @Override
    public void run(){
        while(true)
        {
            synchronized(sharedBuffer){
                while(currLoc==0)
                {
                    try
                    {
                        System.out.println("Integer buffer is empty.");
                        sharedBuffer.wait();
                    }
                    catch(InterruptedException e)
                    {
                        e.printStackTrace();
                    }
                }
                int number = sharedBuffer[currLoc];
                sharedBuffer[currLoc] = -1;
                --currLoc;
                System.out.println("Consuming value "+number);
                sharedBuffer.notify();
            }
        }
    }
}