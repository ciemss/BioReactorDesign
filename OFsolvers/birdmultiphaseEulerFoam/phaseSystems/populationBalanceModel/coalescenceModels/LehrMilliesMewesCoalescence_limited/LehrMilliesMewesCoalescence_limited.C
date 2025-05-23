/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019-2021 OpenFOAM Foundation
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

#include "LehrMilliesMewesCoalescence_limited.H"
#include "addToRunTimeSelectionTable.H"
#include "mathematicalConstants.H"
#include "phaseDynamicMomentumTransportModel.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace diameterModels
{
namespace coalescenceModels
{
    defineTypeNameAndDebug(LehrMilliesMewesCoalescence_limited, 0);
    addToRunTimeSelectionTable
    (
        coalescenceModel,
        LehrMilliesMewesCoalescence_limited,
        dictionary
    );
}
}
}

using Foam::constant::mathematical::pi;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::diameterModels::coalescenceModels::LehrMilliesMewesCoalescence_limited::
LehrMilliesMewesCoalescence_limited
(
    const populationBalanceModel& popBal,
    const dictionary& dict
)
:
    coalescenceModel(popBal, dict),
    efficiency_
    (
        dimensionedScalar::lookupOrDefault("efficiency", dict, dimless, 1.0)
    ),
    uCrit_
    (
        dimensionedScalar::lookupOrDefault("uCrit", dict, dimVelocity, 0.08)
    ),
    alphaMax_
    (
        dimensionedScalar::lookupOrDefault("alphaMax", dict, dimless, 0.6)
    ),
    height_lim_("height_lim", dimless, dict),
    height_dir_("height_dir", dimless, dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void
Foam::diameterModels::coalescenceModels::LehrMilliesMewesCoalescence_limited::
addToCoalescenceRate
(
    volScalarField& coalescenceRate,
    const label i,
    const label j
)
{
    const sizeGroup& fi = popBal_.sizeGroups()[i];
    const sizeGroup& fj = popBal_.sizeGroups()[j];

    const volScalarField uChar
    (
        max
        (
            sqrt(2.0)*cbrt(popBal_.continuousTurbulence().epsilon())
           *sqrt(cbrt(sqr(fi.dSph())) + cbrt(sqr(fj.dSph()))),
            mag(fi.phase().U() - fj.phase().U())
        )
    );

    coalescenceRate +=
       efficiency_ * (pi/4*sqr(fi.dSph() + fj.dSph())*min(uChar, uCrit_)
       *exp
        (
          - sqr(cbrt(alphaMax_)
           /cbrt(max(popBal_.alphas(), fi.phase().residualAlpha())) - 1)
        ));
   volVectorField centres = coalescenceRate.ref().mesh().C();
   int dir = int (height_dir_.value());
   forAll(centres, cellI) {
       if (centres[cellI][dir]>height_lim_.value()) {
           coalescenceRate.ref()[cellI] = 0.0;
       }
   } 
}


// ************************************************************************* //
