/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "sphericalHeatTransfer_limited.H"
#include "phasePair.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace heatTransferModels
{
    defineTypeNameAndDebug(sphericalHeatTransfer_limited, 0);
    addToRunTimeSelectionTable
    (
        heatTransferModel,
        sphericalHeatTransfer_limited,
        dictionary
    );
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::heatTransferModels::sphericalHeatTransfer_limited::sphericalHeatTransfer_limited
(
    const dictionary& dict,
    const phasePair& pair
)
:
    heatTransferModel(dict, pair),
    height_lim_("height_lim", dimless, dict),
    height_dir_("height_dir", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::heatTransferModels::sphericalHeatTransfer_limited::~sphericalHeatTransfer_limited()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::heatTransferModels::sphericalHeatTransfer_limited::K
(
    const scalar residualAlpha
) const
{

    Foam::tmp<Foam::volScalarField> K = 60.0
       *max(pair_.dispersed(), residualAlpha)
       *pair_.dispersed().thermo().kappa()
       /sqr(pair_.dispersed().d());
    volVectorField centres = K.ref().mesh().C();
    int dir = int (height_dir_.value());
    forAll(centres, cellI) {
        if (centres[cellI][dir]>height_lim_.value()) {
            K.ref()[cellI] = 0.0;
        }
    }
    return K;
}


// ************************************************************************* //
