public class Producer extends Thread {
    int[] sharedBuffer;
    int currLoc;
    int number = 0;

    Producer(int[] sharedBuffer, int currLoc){
        this.sharedBuffer = sharedBuffer;
        this.currLoc = currLoc;
        number = currLoc+1;
    }

    @Override
    public void run(){
        while(true)
        {
            synchronized(sharedBuffer){
                while((sharedBuffer.length-1) == currLoc)
                {
                    try
                    {
                        System.out.println("Integer buffer is full.");
                        sharedBuffer.wait();
                    }
                    catch(InterruptedException e)
                    {
                        e.printStackTrace();
                    }
                }
                System.out.println("Producing value "+ number);
                sharedBuffer[currLoc] = number;
                sharedBuffer.notify();
            }
        }
    }
}