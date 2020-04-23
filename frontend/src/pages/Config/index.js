import React, { useState } from 'react';
import { useHistory } from 'react-router-dom';

import './styles.css';

import api from '../../services/api';

export default function Config(){
    const [peristalticPumpNumber, peristalticPumpNumberState] = useState();
    const [peristalticPumpRatio, peristalticPumpRatioState] = useState();
    const [peristalticPumpTempOn, peristalticPumpTempOnState] = useState();
    const [peristalticPumpTurn, peristalticPumpTurnState] = useState();
    const [peristalticPumpTurningDirection, peristalticPumpTurningDirectionState] = useState();
    const history= useHistory();

    async function handleConfigurePeristalticPump(e){
        e.preventDefault();

        try{
            const response = await api.post('bomb', { peristalticPumpNumber, peristalticPumpRatio, peristalticPumpTempOn, peristalticPumpTurn, peristalticPumpTurningDirection });
            localStorage.setItem('peristalticPumpNumber', response.peristalticPumpNumber);
            localStorage.setItem('peristalticPumpRatio', response.peristalticPumpRatio);
            localStorage.setItem('peristalticPumpTempOn', response.peristalticPumpTempOn);
            localStorage.setItem('peristalticPumpTurn', response.peristalticPumpTurn);
            localStorage.setItem('peristalticPumpTurningDirection', response.peristalticPumpTurningDirection);

            alert(`Bomba peristaltica ${peristalticPumpNumber} esta configurada.`);
            history.push('/');
        }catch (err){
            alert(`Falha no configuração da bomba peristaltica ${peristalticPumpNumber}, tente novamente.\n ${err}`);

        }
    }


    return (
        <div className="conteiner">
            <section className="form">
                <h1>Dosadores Peristalticos</h1> <br />
                <form onSubmit={handleConfigurePeristalticPump}>
                    <h2>Configurar Bomba Peristaltica</h2><br />

                    <h3>Numero da bomba a ser configurada</h3>
                    <input 
                        type="number"
                        placeholder="Numero"
                        value={peristalticPumpNumber}
                        onChange={e => peristalticPumpNumberState( e.target.value )}
                        min="1"
                        max="4"
                    />  

                    <h3>Proporção da largura de pulso de 0 a 100%</h3>
                    <input
                        type="number"
                        placeholder="%"
                        value={peristalticPumpRatio}
                        onChange={e => peristalticPumpRatioState( e.target.value )}
                        min="0"
                        max="100"
                    />

                    <h3>Proporção do tempo que bomba devera esta ligada de 0 a 100% a cada minuto</h3>                
                    <input
                        type="number"
                        placeholder="%"
                        value={peristalticPumpTempOn}
                        onChange={e => peristalticPumpTempOnState( e.target.value )}
                        min="0"
                        max="100"
                    />

                    <h3>Direção</h3>
                    <select
                        value={peristalticPumpTurningDirection}
                        onChange={e => peristalticPumpTurningDirectionState( e.target.value )}
                    >
                        <option value="">Vazio</option>
                        <option value="1">Horario</option>
                        <option value="0">Anti-Horario</option>
                    </select>

                    <h3>Estado</h3>
                    <select
                        value={peristalticPumpTurn}
                        onChange={e => peristalticPumpTurnState( e.target.value )}
                    >
                        <option value="">Vazio</option>
                        <option value="1">Ligar</option>
                        <option value="0">Desligar</option>
                    </select>

                    <button className="button" type="submit">Configurar</button>

                </form>
            </section>
        </div>
    );
}