
class Pd2Mo {
	/**
	 * Tranform the modelCoupled to a AST_StoredDefinition.
         * @param string path of from where get the Modelica .mo files
         * iteramos sobre cada modelChild, 
		a) segun el path agreagamos a nuestros modelos los modelos (reescribimos las variables) 
		b) seteamos los parametros (esto depende de como los leamos)
		c) conectamos los componentes.
         */ 

	//TODO:AST_StoredDefinition transform(string path, modelCoupled c);

	/**
	  * Load the modelica Class acording with the modelCoupled/modelChild
	  */
	AST_ClassList loadClass(string path, modelCoupled c);
	//TODO: AST_ClassList rewriteModelicaVariables(string path, AST_ClassList classList);
	//AST_StoredDefinition connectVariables(string path, AST_ClassList classList, modelCoupled c);
}
