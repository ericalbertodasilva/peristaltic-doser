import React from 'react';
import {BrowserRouter, Route, Switch} from 'react-router-dom';

import Config from './pages/Config';

export default function Routes(){
    return(
        <BrowserRouter>
            <Switch>
                <Route path='/' exact component={Config}/>
            </Switch>
        </BrowserRouter>
    )

}

// npm install axios
// npm install react-router-dom