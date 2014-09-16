#include "sockdateturnel.h"

sockDateTurnel::sockDateTurnel(qintptr s1Descriptor, qintptr s2Descriptor)
{
    this->s1d = s1Descriptor;
    this->s2d = s2Descriptor;
    this->in = NULL;
    this->out = NULL;
    run_state = 1;
}

void sockDateTurnel::run(){
    in = new QTcpSocket;
    in->setSocketDescriptor(s1d);

    out = new QTcpSocket;
    out->setSocketDescriptor(s2d);

    while(1==run_state){
        try{
            if(this->s1d == in->socketDescriptor() && this->s2d == out->socketDescriptor()){
                in->waitForReadyRead(-1);
                buffer = in->readAll();
//                qDebug()<<"Recv Sth ! \n";
                if(buffer.length()>=0 ){
                    out->write(buffer);
                    out->waitForBytesWritten(-1);
                }
            }
            else{
                qDebug()<< "<<<the stream is error ! \n"<< endl;
                break;
            }
        }
        catch (int number){
            qDebug()<<"Something Wrong ! \n\t No." << number<< endl;
            break;
        }
    }
    CloseSocks();
    return ;
}

void sockDateTurnel::CloseSocks(){
    this->run_state = 0;
    qDebug()<< "<<<<<<one way close ";
    return ;
}

int sockDateTurnel::RunningNow(){
    return this->run_state;
}
