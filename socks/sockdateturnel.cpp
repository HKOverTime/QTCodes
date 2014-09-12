#include "sockdateturnel.h"

sockDateTurnel::sockDateTurnel(qintptr s1Descriptor, qintptr s2Descriptor)
{
    this->s1d = s1Descriptor;
    this->s2d = s2Descriptor;
    this->in = NULL;
    this->out = NULL;
}

void sockDateTurnel::run(){
    in = new QTcpSocket;
    in->setSocketDescriptor(s1d);
    out = new QTcpSocket;
    out->setSocketDescriptor(s2d);
    while(1){
        try{
            if(in!=NULL){
                in->waitForReadyRead(-1);
                buffer = in->readAll();
                if(buffer.length()>=0 && out!=NULL){
                    out->write(buffer);
                    out->waitForBytesWritten(-1);
                }
                else{
                    qDebug()<< "read buffer Error ! \n"<< endl;
                    break;
                }
            }
            else{
                qDebug()<< "in stream is NULL ! \n"<< endl;
                break;
            }
        }
        catch (int number){
            qDebug()<<"Something Wrong ! \n\t No." << number<< endl;
            break;
        }
    }
}
