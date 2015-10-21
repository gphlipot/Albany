//*****************************************************************//
//    Albany 2.0:  Copyright 2012 Sandia Corporation               //
//    This Software is released under the BSD license detailed     //
//    in the file "license.txt" in the top-level Albany directory  //
//*****************************************************************//

#include "GOAL_BCUtils.hpp"
#include "Albany_Application.hpp"
#include "Albany_GOALDiscretization.hpp"
#include "GOAL_MechanicsProblem.hpp"

using Teuchos::RCP;
using Teuchos::ParameterList;

namespace GOAL {

class BCManager
{
  public:
    BCManager(
        Albany::Application const& application,
        RCP<Tpetra_Vector> const& residual,
        RCP<Tpetra_CrsMatrix> const& jacobian);
    void run();
  private:
    void applyBC(Teuchos::ParameterList const& p);
    Albany::Application const& app;
    RCP<Tpetra_Vector> const& res;
    RCP<Tpetra_CrsMatrix> const& jac;
    RCP<Albany::GOALDiscretization> disc;
    RCP<Albany::GOALMeshStruct> meshStruct;
    RCP<Albany::GOALMechanicsProblem> problem;
    Albany::GOALNodeSets ns;
    ParameterList bcParams;
};

BCManager::BCManager(
    Albany::Application const& application,
    RCP<Tpetra_Vector> const& residual,
    RCP<Tpetra_CrsMatrix> const& jacobian) :
  app(application),
  res(residual),
  jac(jacobian)
{
  RCP<const ParameterList> pl = app.getProblemPL();
  bcParams = pl->sublist("Hierarchic Boundary Conditions");
  RCP<Albany::AbstractDiscretization> ad = app.getDiscretization();
  disc = Teuchos::rcp_dynamic_cast<Albany::GOALDiscretization>(ad);
  meshStruct = disc->getGOALMeshStruct();
  RCP<Albany::AbstractProblem> ap = app.getProblem();
  problem = Teuchos::rcp_dynamic_cast<Albany::GOALMechanicsProblem>(ap);
  ns = disc->getGOALNodeSets();
}

void BCManager::run()
{
  typedef ParameterList::ConstIterator ParamIter;
  for (ParamIter i = bcParams.begin(); i != bcParams.end(); ++i)
  {
    std::string const& name = bcParams.name(i);
    Teuchos::ParameterEntry const& entry = bcParams.entry(i);
    assert(entry.isList());
    applyBC(Teuchos::getValue<ParameterList>(entry));
  }
}

static RCP<ParameterList> getValidBCParameters()
{
  RCP<ParameterList> p = rcp(new ParameterList("Valid Hierarchic BC Params"));
  p->set<std::string>("DOF", "", "Degree of freedom to which BC is applied");
  p->set<double>("Value", 0.0, "Value of the BC as function of t");
  p->set<std::string>("Node Set", "", "Node Set to apply the BC to");
  return p;
}

void BCManager::applyBC(ParameterList const& p)
{
  // validate parameters
  RCP<ParameterList> vp = getValidBCParameters();
  p.validateParameters(*vp,0);

  // get the input parameters
  double v = p.get<double>("Value");
  std::string set = p.get<std::string>("Node Set");
  std::string dof = p.get<std::string>("DOF");

  // does this node set actually exist?
  assert(ns.count(set) == 1);

  // does this dof actually exist?
  int offset = problem->getOffset(dof);

  std::cout << "OFFSET " << offset << std::endl;

}

void computeHierarchicBCs(
    Albany::Application const& app,
    RCP<Tpetra_Vector> const& res,
    RCP<Tpetra_CrsMatrix> const& jac)
{
  RCP<const ParameterList> pl = app.getProblemPL();
  std::string name = pl->get<std::string>("Name");
  if (name.find("GOAL") != 0)
    return;
  BCManager bcm(app, res, jac);
  bcm.run();
}

}