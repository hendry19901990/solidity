/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <libsolidity/formal/SolverInterface.h>
#include <libsolidity/formal/SymbolicVariables.h>

#include <unordered_map>
#include <set>

namespace dev
{
namespace solidity
{
namespace smt
{

/**
 * Stores the context of the SMT encoding.
 */
class EncodingContext
{
public:
	EncodingContext(std::shared_ptr<SolverInterface> _solver);

	EncodingContext(EncodingContext const& _other) = default;
	EncodingContext& operator=(EncodingContext const& _other) = default;

	/// Resets the entire context.
	void reset();

	/// Methods related to variables.
	//@{
	/// @returns the symbolic representation of a program variable.
	std::shared_ptr<SymbolicVariable> variable(solidity::VariableDeclaration const& _varDecl);
	/// @returns all symbolic variables.
	std::unordered_map<solidity::VariableDeclaration const*, std::shared_ptr<SymbolicVariable>> const& variables() const { return m_variables; }

	/// Creates a symbolic variable and
	/// @returns true if a variable's type is not supported and is therefore abstract.
	bool createVariable(solidity::VariableDeclaration const& _varDecl);
	/// @returns true if variable was created.
	bool knownVariable(solidity::VariableDeclaration const& _varDecl);

	/// Resets a specific variable.
	void resetVariable(solidity::VariableDeclaration const& _variable);
	/// Resets a set of variables.
	void resetVariables(std::set<solidity::VariableDeclaration const*> const& _variables);
	/// Resets variables according to a predicate.
	void resetVariables(std::function<bool(solidity::VariableDeclaration const&)> const& _filter);
	///Resets all variables.
	void resetAllVariables();
	void resetAllExpressions();

	/// Allocates a new index for the declaration, updates the current
	/// index to this value and returns the expression.
	Expression newValue(solidity::VariableDeclaration const& _decl);
	/// Sets the value of the declaration to zero.
	void setZeroValue(solidity::VariableDeclaration const& _decl);
	void setZeroValue(SymbolicVariable& _variable);
	/// Resets the variable to an unknown value (in its range).
	void setUnknownValue(solidity::VariableDeclaration const& decl);
	void setUnknownValue(SymbolicVariable& _variable);
	//@}

	/// Methods related to expressions.
	////@{
	/// @returns the symbolic representation of an AST node expression.
	std::shared_ptr<SymbolicVariable> expression(solidity::Expression const& _e);
	/// @returns all symbolic expressions.
	std::unordered_map<solidity::Expression const*, std::shared_ptr<SymbolicVariable>> const& expressions() const { return m_expressions; }

	/// Creates the expression (value can be arbitrary).
	/// @returns true if type is not supported.
	bool createExpression(solidity::Expression const& _e, std::shared_ptr<SymbolicVariable> _symbExpr = nullptr);
	/// Checks if expression was created.
	bool knownExpression(solidity::Expression const& _e) const;
	//@}

	/// Methods related to global variables and functions.
	//@{
	/// Global variables and functions.
	std::shared_ptr<SymbolicVariable> globalSymbol(std::string const& _name);
	/// @returns all symbolic variables.
	std::unordered_map<std::string, std::shared_ptr<SymbolicVariable>> const& globalSymbols() const;
	/// Defines a new global variable or function
	/// and @returns true if type was abstracted.
	bool createGlobalSymbol(std::string const& _name, solidity::Expression const& _expr);
	/// Checks if special variable or function was seen.
	bool knownGlobalSymbol(std::string const& _var) const;
	//@}

	/// Methods related to SSA.
	//@{
	/// Maps a symbolic variable to an SSA index.
	using VariableIndices = std::unordered_map<ASTNode const*, int>;
	/// Copy the SSA indices of m_variables.
	VariableIndices copyVariableIndices() const;
	/// Backs up the SSA indices at a certain node.
	void saveVariableIndices(ASTNode const* _node);
	std::vector<VariableIndices> const& ssaIndices(ASTNode const* _node) const
	{
		return m_ssaIndices.at(_node);
	}
	//@}

	/// Methods related to the solver.
	//@{
	void saveConstraints(Expression const& _constraints)
	{
		m_constraints = _constraints;
	}
	Expression const& constraints() const
	{
		return m_constraints;
	}
	//@}

	/// Methods related to the state of the checker.
	//@{
	void saveIntermediateContext(ASTNode const* _node);
	std::shared_ptr<EncodingContext> intermediateContext(ASTNode const* _node)
	{
		return m_intermediateContexts.at(_node);
	}
	//@}

	/// Blockchain related methods.
	//@{
	/// Value of `this` address.
	Expression thisAddress();
	/// @returns the symbolic balance of address `this`.
	Expression balance();
	/// @returns the symbolic balance of an address.
	Expression balance(Expression _address);
	/// Transfer _value from _from to _to.
	void transfer(Expression _from, Expression _to, Expression _value);
	//@}

private:
	/// Adds _value to _account's balance.
	void addBalance(Expression _account, Expression _value);

	std::shared_ptr<SolverInterface> m_solver;

	/// Intermediate contexts at specific nodes.
	std::unordered_map<ASTNode const*, std::shared_ptr<EncodingContext>> m_intermediateContexts;

	/// Symbolic variables.
	std::unordered_map<solidity::VariableDeclaration const*, std::shared_ptr<SymbolicVariable>> m_variables;

	/// Symbolic expressions.
	std::unordered_map<solidity::Expression const*, std::shared_ptr<SymbolicVariable>> m_expressions;

	/// Symbolic representation of global symbols including
	/// variables and functions.
	std::unordered_map<std::string, std::shared_ptr<smt::SymbolicVariable>> m_globalContext;

	/// SSA indices at specific breakpoints.
	std::unordered_map<ASTNode const*, std::vector<VariableIndices>> m_ssaIndices;

	/// Constraints at specific breakpoints.
	Expression m_constraints;

	/// Symbolic `this` address.
	std::shared_ptr<SymbolicAddressVariable> m_thisAddress;

	/// Symbolic balances.
	std::shared_ptr<SymbolicVariable> m_balances;
};

}
}
}
