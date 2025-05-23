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

Class
    Foam::diffusiveMassTransferModels::sphericalDiffusiveMassTransfer_limited

Description
    Model which applies an analytical solution for mass transfer from the
    surface of a sphere to the fluid within the sphere.

SourceFiles
    sphericalDiffusiveMassTransfer_limited.C

\*---------------------------------------------------------------------------*/

#ifndef sphericalDiffusiveMassTransfer_limited_H
#define sphericalDiffusiveMassTransfer_limited_H

#include "diffusiveMassTransferModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class phasePair;

namespace diffusiveMassTransferModels
{

/*---------------------------------------------------------------------------*\
               Class sphericalDiffusiveMassTransfer_limited Declaration
\*---------------------------------------------------------------------------*/

class sphericalDiffusiveMassTransfer_limited
:
    public diffusiveMassTransferModel
{
    // Private Data

        //- Lewis number
        const dimensionedScalar Le_;
        //- Where to zero out
        const dimensionedScalar height_lim_;
        const dimensionedScalar height_dir_;

public:

    //- Runtime type information
    TypeName("spherical_limited");


    // Constructors

        //- Construct from components
        sphericalDiffusiveMassTransfer_limited
        (
            const dictionary& dict,
            const phasePair& pair
        );


    //- Destructor
    virtual ~sphericalDiffusiveMassTransfer_limited();


    // Member Functions

        //- The implicit mass transfer coefficient
        virtual tmp<volScalarField> K() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace diffusiveMassTransferModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
