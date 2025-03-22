'use client'

const mailboxList: Map<string, IMailbox> = new Map();

export function registerMailbox(component: IMailbox) {
    mailboxList.set(component.getName(), component);
}

export function unregisterMailbox(component: IMailbox) {
    mailboxList.delete(component.getName());
}

export interface IMail<T> {
    subject: string;
    content: T;
}

export interface IMailbox {
    getName(): string;

    sendMail<T>(subject: string, content: T): unknown;

    sendTypedMail<T>(mail: IMail<T>): unknown;

    receiveMail<T>(subject: string): IMail<T> | undefined;

    subscribe<T>(subject: string, callback: (mail: IMail<T>) => void): Symbol;

    unsubscribe(stub: Symbol): void;
}

class ClientMailbox implements IMailbox {
    private mailList: IMail<any>[] = [];
    private subscribers: Map<Symbol, ((mail: IMail<any>) => void)> = new Map();
    private readonly mailboxName: string = '';

    constructor(mailboxName: string) {
        this.mailboxName = mailboxName;
    }

    getName(): string {
        return this.mailboxName;
    }

    sendMail<T>(subject: string, content: T): unknown {
        this.mailList.push({
            subject,
            content
        });
        this.subscribers.forEach(subscriber => {
            subscriber({
                subject,
                content
            });
        });
        return undefined;
    }


    sendTypedMail<T>(mail: IMail<T>): unknown {
        this.mailList.push(mail);
        return undefined;
    }

    receiveMail<T>(subject: string): IMail<T> | undefined {
        return this.mailList.find(mail => mail.subject === subject);
    }

    subscribe<T>(subject: string, callback: (mail: IMail<T>) => void): Symbol {

        const stub = Symbol();
        this.subscribers.set(stub, (mail) => {
            if (subject !== mail.subject) {
                return;
            }
            callback(mail);
        });
        return stub;
    }

    unsubscribe(stub: Symbol): void {
        this.subscribers.delete(stub);
    }
}

export function createClientMailbox(name: string) {
    return new ClientMailbox(name);
}
