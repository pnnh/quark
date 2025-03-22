
export function resolvePath(path: string): string {
    const filePrefix = 'file://'
    let newPath = path
    if (newPath.startsWith(filePrefix)) {
        newPath = newPath.replace(filePrefix, '')
    }
    if (newPath.startsWith("~/")) {
        newPath = newPath.replace("~/", process.env.HOME + "/")
    } else if (newPath.startsWith("./")) {
        newPath = newPath.replace("./", process.cwd() + "/")
    }
    return newPath
}
