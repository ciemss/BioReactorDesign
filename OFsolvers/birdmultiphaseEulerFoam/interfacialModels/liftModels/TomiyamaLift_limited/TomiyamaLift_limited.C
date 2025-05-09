/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2020 OpenFOAM Foundation
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

#include "TomiyamaLift_limited.H"
#include "phasePair.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace liftModels
{
    defineTypeNameAndDebug(TomiyamaLift_limited, 0);
    addToRunTimeSelectionTable(liftModel, TomiyamaLift_limited, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::liftModels::TomiyamaLift_limited::TomiyamaLift_limited
(
    const dictionary& dict,
    const phasePair& pair
)
:
    liftModel(dict, pair),
    height_lim_("height_lim", dimless, dict),
    height_dir_("height_dir", dimless, dict)
{}



// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::liftModels::TomiyamaLift_limited::~TomiyamaLift_limited()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField> Foam::liftModels::TomiyamaLift_limited::Cl() const
{
    const volScalarField EoH(pair_.EoH2());

    const volScalarField f
    (
        0.0010422*pow3(EoH) - 0.0159*sqr(EoH) - 0.0204*EoH + 0.474
    );

    Foam::tmp<Foam::volScalarField> Cl = neg(EoH - 4)*min(0.288*tanh(0.121*pair_.Re()), f)
      + pos0(EoH - 4)*neg(EoH - 10.7)*f
      + pos0(EoH - 10.7)*(-0.288);

    volVectorField centres = Cl.ref().mesh().C();
    int dir = int (height_dir_.value());
    forAll(centres, cellI) {
        if (centres[cellI][dir]>height_lim_.value()) {
            Cl.ref()[cellI] = 0.0;
        }
    }
    return Cl;
}


// ************************************************************************* //
