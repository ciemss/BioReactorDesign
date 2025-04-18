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

Class
    Foam::wallLubricationModels::Antal_limited

Description
    Wall lubrication model of Antal_limited et al.

    Reference:
    \verbatim
        Antal_limited, S. P., Lahey Jr, R. T., & Flaherty, J. E. (1991).
        Analysis of phase distribution in fully developed laminar bubbly
        two-phase flow.
        International Journal of Multiphase Flow, 17(5), 635-652.
    \endverbatim

SourceFiles
    Antal_limited.C

\*---------------------------------------------------------------------------*/

#ifndef Antal_limited_H
#define Antal_limited_H

#include "wallLubricationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class phasePair;

namespace wallLubricationModels
{

/*---------------------------------------------------------------------------*\
                            Class Antal_limited Declaration
\*---------------------------------------------------------------------------*/

class Antal_limited
:
    public wallLubricationModel
{
    // Private Data

        //- Coefficient 1
        const dimensionedScalar Cw1_;

        //- Coefficient 2
        const dimensionedScalar Cw2_;

        //- Where to zero out
        const dimensionedScalar height_lim_;
        const dimensionedScalar height_dir_;

public:

    //- Runtime type information
    TypeName("Antal_limited");


    // Constructors

        //- Construct from components
        Antal_limited
        (
            const dictionary& dict,
            const phasePair& pair
        );


    //- Destructor
    virtual ~Antal_limited();


    // Member Functions

        //- Return phase-intensive wall lubrication force
        tmp<volVectorField> Fi() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace wallLubricationModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
