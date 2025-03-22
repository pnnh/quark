export class ButtonThrottle {
    #times: number = 0
    #duration: number = 1000

    constructor(duration: number = 1000) {
        console.log('Hello, Throttle!')
        this.#duration = duration
    }

    async throttle(): Promise<boolean> {
        return new Promise((resolve) => {
            if (this.#times > 0) {
                resolve(false)
            }
            resolve(true)
            this.#times += 1
            setTimeout(() => {
                this.#times -= 1
            }, this.#duration)
        })
    }
}

export async function buttonThrottle(duration: number = 1000) {
    console.log('Hello, Throttle2!')
    return new Promise((resolve) => {
        setTimeout(() => {
            resolve('Throttle Done')
        }, duration)
    })
}
