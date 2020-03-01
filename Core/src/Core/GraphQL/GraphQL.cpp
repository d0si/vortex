#include <Core/GraphQL/GraphQL.h>
#include <string>
#include <iostream>
#ifdef VORTEX_HAS_FEATURE_GRAPHQL
#include <graphqlparser/Ast.h>
#include <graphqlparser/GraphQLParser.h>
#include <graphqlparser/c/GraphQLAstToJSON.h>
#endif

namespace Vortex {
	namespace Core {
		namespace GraphQL {
			void GraphQL::parse() {
#ifdef VORTEX_HAS_FEATURE_GRAPHQL
				const char* error = nullptr;

				auto AST = facebook::graphql::parseString("{field(arg: null)}", &error);

				const char* json = graphql_ast_to_json(reinterpret_cast<const struct GraphQLAstNode*>(AST.get()));

				// json response
				std::cout << json;

				free((void*)json);
#endif
			}
		}  // namespace GraphQL
	}  // namespace Core
}  // namespace Vortex
