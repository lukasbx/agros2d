// This file is part of Agros2D.
//
// Agros2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Agros2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Agros2D.  If not, see <http://www.gnu.org/licenses/>.
//
// hp-FEM group (http://hpfem.org/)
// University of Nevada, Reno (UNR) and University of West Bohemia, Pilsen
// Email: agros2d@googlegroups.com, home page: http://hpfem.org/agros2d/

#ifndef WEAKFORM_PARSER_H
#define WEAKFORM_PARSER_H

#include "util.h"
#include <weakform/weakform.h>
#include "boundary.h"
#include "material.h"

#include <rapidxml.cpp>
#include <rapidxml_utils.cpp>

class Parser;

struct ParserFormMatrix
{
    ParserFormMatrix() : i(0), j(0), sym(Hermes::Hermes2D::HERMES_NONSYM), expression("") {}
    ParserFormMatrix(rapidxml::xml_node<> *node, ProblemType problem_type);

    // position
    int i;
    int j;

    // symmetric flag
    Hermes::Hermes2D::SymFlag sym;

    // expression
    std::string expression;
};

struct ParserFormVector
{
    ParserFormVector() : i(0), expression("") {}
    ParserFormVector(rapidxml::xml_node<> *node, ProblemType problem_type);

    // position
    int i;

    // expression
    std::string expression;
};

class ParserForm
{
public:
    Parser *parser;

    // coordinates
    double px;
    double py;

    // current solution
    double puval;
    double pudx;
    double pudy;

    // test function
    double pvval;
    double pvdx;
    double pvdy;

    // previous solution
    double pupval;
    double pupdx;
    double pupdy;

    ParserForm();
    ~ParserForm();

    void initParser(Material *material, Boundary *boundary);
};

// **********************************************************************************************

template<typename Scalar>
class CustomParserMatrixFormVol : public Hermes::Hermes2D::MatrixFormVol<Scalar>, public ParserForm
{
public:
    CustomParserMatrixFormVol(unsigned int i, unsigned int j,
                              std::string area,
                              Hermes::Hermes2D::SymFlag sym,
                              std::string expression,
                              Material *material);

    virtual Scalar value(int n, double *wt, Hermes::Hermes2D::Func<Scalar> *u_ext[], Hermes::Hermes2D::Func<double> *u,
                         Hermes::Hermes2D::Func<double> *v, Hermes::Hermes2D::Geom<double> *e, Hermes::Hermes2D::ExtData<Scalar> *ext);
    virtual Hermes::Ord ord(int n, double *wt, Hermes::Hermes2D::Func<Hermes::Ord> *u_ext[], Hermes::Hermes2D::Func<Hermes::Ord> *u,
                            Hermes::Hermes2D::Func<Hermes::Ord> *v, Hermes::Hermes2D::Geom<Hermes::Ord> *e, Hermes::Hermes2D::ExtData<Hermes::Ord> *ext) const;
};

template<typename Scalar>
class CustomParserVectorFormVol : public Hermes::Hermes2D::VectorFormVol<double>, public ParserForm
{
public:
    CustomParserVectorFormVol(unsigned int i,
                              std::string area, std::string expression,
                              Material *material,
                              Hermes::vector<Hermes::Hermes2D::MeshFunction<Scalar> *> solution);

    virtual Scalar value(int n, double *wt, Hermes::Hermes2D::Func<Scalar> *u_ext[],Hermes::Hermes2D::Func<double> *v,
                         Hermes::Hermes2D::Geom<double> *e, Hermes::Hermes2D::ExtData<Scalar> *ext);
    virtual Hermes::Ord ord(int n, double *wt, Hermes::Hermes2D::Func<Hermes::Ord> *u_ext[], Hermes::Hermes2D::Func<Hermes::Ord> *v,
                              Hermes::Hermes2D::Geom<Hermes::Ord> *e, Hermes::Hermes2D::ExtData<Hermes::Ord> *ext) const;
};

// **********************************************************************************************

template<typename Scalar>
class CustomParserMatrixFormSurf : public Hermes::Hermes2D::MatrixFormSurf<Scalar>, public ParserForm
{
public:
    CustomParserMatrixFormSurf(unsigned int i, unsigned int j,
                              std::string area, std::string expression,
                              Boundary *boundary);

    virtual Scalar value(int n, double *wt, Hermes::Hermes2D::Func<Scalar> *u_ext[], Hermes::Hermes2D::Func<double> *u, Hermes::Hermes2D::Func<double> *v,
                         Hermes::Hermes2D::Geom<double> *e, Hermes::Hermes2D::ExtData<Scalar> *ext);
    virtual Hermes::Ord ord(int n, double *wt, Hermes::Hermes2D::Func<Hermes::Ord> *u_ext[], Hermes::Hermes2D::Func<Hermes::Ord> *u, Hermes::Hermes2D::Func<Hermes::Ord> *v,
                    Hermes::Hermes2D::Geom<Hermes::Ord> *e, Hermes::Hermes2D::ExtData<Hermes::Ord> *ext) const;
};

template<typename Scalar>
class CustomParserVectorFormSurf : public Hermes::Hermes2D::VectorFormSurf<Scalar>, public ParserForm
{
public:
    CustomParserVectorFormSurf(unsigned int i,
                              std::string area, std::string expression,
                              Boundary *boundary);

    virtual Scalar value(int n, double *wt, Hermes::Hermes2D::Func<Scalar> *u_ext[], Hermes::Hermes2D::Func<double> *v,
                         Hermes::Hermes2D::Geom<double> *e, Hermes::Hermes2D::ExtData<Scalar> *ext);
    virtual Hermes::Ord ord(int n, double *wt, Hermes::Hermes2D::Func<Hermes::Ord> *u_ext[], Hermes::Hermes2D::Func<Hermes::Ord> *v,
                      Hermes::Hermes2D::Geom<Hermes::Ord> *e, Hermes::Hermes2D::ExtData<Hermes::Ord> *ext) const;
};

#endif // WEAKFORM_PARSER_H