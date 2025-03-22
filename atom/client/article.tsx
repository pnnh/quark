import React from "react";
import './editor.scss'

export function ArticleComponent({children}: {
    children: React.ReactNode
}) {
    return <div>
        {children}
    </div>
}
