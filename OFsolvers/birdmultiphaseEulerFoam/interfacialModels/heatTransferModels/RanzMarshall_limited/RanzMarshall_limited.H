/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
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
    Foam::heatTransferModels::RanzMarshall_limited

Description
    Ranz-Marshall correlation for turbulent heat transfer from the surface of a
    sphere to the surrounding fluid.

SourceFiles
    RanzMarshall_limited.C

\*---------------------------------------------------------------------------*/

#ifndef RanzMarshall_limited_H
#define RanzMarshall_limited_H

#include "heatTransferModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace heatTransferModels
{

/*---------------------------------------------------------------------------*\
                        Class RanzMarshall_limited Declaration
\*---------------------------------------------------------------------------*/

class RanzMarshall_limited
:
    public heatTransferModel
{

    //- Where to zero out
    const dimensionedScalar height_lim_;
    const dimensionedScalar height_dir_;

public:

    //- Runtime type information
    TypeName("RanzMarshall_limited");


    // Constructors

        //- Construct from components
        RanzMarshall_limited
        (
            const dictionary& dict,
            const phasePair& pair
        );


    //- Destructor
    virtual ~RanzMarshall_limited();


    // Member Functions

        //- The heat transfer function K used in the enthalpy equation
        tmp<volScalarField> K(const scalar residualAlpha) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace heatTransferModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
