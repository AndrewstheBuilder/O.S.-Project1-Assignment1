import java.util.Stack;
import java.util.concurrent.ThreadLocalRandom;

class Producer extends Thread {
    Stack<Integer> sharedBuffer;
    int maxSize;
    int number = 0;

    Producer(Stack<Integer> sharedBuffer, int maxSize){
        this.sharedBuffer = sharedBuffer;
        this.maxSize = maxSize;
        number = ThreadLocalRandom.current().nextInt(20) + 1;
    }

    @Override
    public void run(){
        while(true)
        {
            synchronized(sharedBuffer){
                while((sharedBuffer.size()) == maxSize)
                {
                    try
                    {
                        System.out.println("Producer is waiting. Integer buffer is full.");
                        sharedBuffer.wait();
                        Thread.sleep(1000);
                    }
                    catch(InterruptedException e)
                    {
                        e.printStackTrace();
                    }
                }
                try
                {
                    if(sharedBuffer.size()==8){
                        sharedBuffer.wait();
                        Thread.sleep(100);
                    }
                }
                catch(InterruptedException ex)
                {
                    ex.printStackTrace();
                }

                System.out.println("Producing value "+ number);
                sharedBuffer.push(number);
                sharedBuffer.notify();
            }
        }
    }
}

class Consumer extends Thread {
    Stack<Integer> sharedBuffer;
    int maxSize;

    Consumer(Stack<Integer> sharedBuffer, int maxSize){
        this.sharedBuffer = sharedBuffer;
        this.maxSize = maxSize;
    }

    @Override
    public void run(){
        while(true)
        {
            synchronized(sharedBuffer){
                while(sharedBuffer.size() == 0)
                {
                    try
                    {
                        System.out.println("Consumer is waiting. Integer buffer is empty.");
                        sharedBuffer.wait();
                        Thread.sleep(1000);
                    }
                    catch(InterruptedException e)
                    {
                        e.printStackTrace();
                    }
                }
                try
                {
                    if(sharedBuffer.size()==2){
                        sharedBuffer.wait();
                        Thread.sleep(100);
                    }
                }
                catch(InterruptedException ex)
                {
                    ex.printStackTrace();
                }
                int number = sharedBuffer.pop();
                System.out.println("Consuming value "+number);
                sharedBuffer.notify();
            }
        }
    }
}

public class Project1 {
    public static void main(String[] args){
        Stack<Integer> sharedIntArray = new Stack<>();
        int maxSize = 10;

        Producer p1 = new Producer(sharedIntArray, maxSize);
        Producer p2 = new Producer(sharedIntArray, maxSize);
        Producer p3 = new Producer(sharedIntArray, maxSize);
        Producer p4 = new Producer(sharedIntArray, maxSize);
        Consumer c1 = new Consumer(sharedIntArray, maxSize);
        Consumer c2 = new Consumer(sharedIntArray, maxSize);
        Consumer c3 = new Consumer(sharedIntArray, maxSize);
        Consumer c4 = new Consumer(sharedIntArray, maxSize);
        p1.start();
        c1.start();
        //p2.start();
        //c2.start();
        try
        {
           p1.join();
           c1.join();
           //c2.join();
           //p2.join();
        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }
    }
}
