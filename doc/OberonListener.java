// Generated from Oberon.g4 by ANTLR 4.10.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link OberonParser}.
 */
public interface OberonListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link OberonParser#qualident}.
	 * @param ctx the parse tree
	 */
	void enterQualident(OberonParser.QualidentContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#qualident}.
	 * @param ctx the parse tree
	 */
	void exitQualident(OberonParser.QualidentContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#identdef}.
	 * @param ctx the parse tree
	 */
	void enterIdentdef(OberonParser.IdentdefContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#identdef}.
	 * @param ctx the parse tree
	 */
	void exitIdentdef(OberonParser.IdentdefContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#number}.
	 * @param ctx the parse tree
	 */
	void enterNumber(OberonParser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#number}.
	 * @param ctx the parse tree
	 */
	void exitNumber(OberonParser.NumberContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#constDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterConstDeclaration(OberonParser.ConstDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#constDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitConstDeclaration(OberonParser.ConstDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#constExpression}.
	 * @param ctx the parse tree
	 */
	void enterConstExpression(OberonParser.ConstExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#constExpression}.
	 * @param ctx the parse tree
	 */
	void exitConstExpression(OberonParser.ConstExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#typeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterTypeDeclaration(OberonParser.TypeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#typeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitTypeDeclaration(OberonParser.TypeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(OberonParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(OberonParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#arrayType}.
	 * @param ctx the parse tree
	 */
	void enterArrayType(OberonParser.ArrayTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#arrayType}.
	 * @param ctx the parse tree
	 */
	void exitArrayType(OberonParser.ArrayTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#length}.
	 * @param ctx the parse tree
	 */
	void enterLength(OberonParser.LengthContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#length}.
	 * @param ctx the parse tree
	 */
	void exitLength(OberonParser.LengthContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#recordType}.
	 * @param ctx the parse tree
	 */
	void enterRecordType(OberonParser.RecordTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#recordType}.
	 * @param ctx the parse tree
	 */
	void exitRecordType(OberonParser.RecordTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#baseType}.
	 * @param ctx the parse tree
	 */
	void enterBaseType(OberonParser.BaseTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#baseType}.
	 * @param ctx the parse tree
	 */
	void exitBaseType(OberonParser.BaseTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#fieldListSequence}.
	 * @param ctx the parse tree
	 */
	void enterFieldListSequence(OberonParser.FieldListSequenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#fieldListSequence}.
	 * @param ctx the parse tree
	 */
	void exitFieldListSequence(OberonParser.FieldListSequenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#fieldList}.
	 * @param ctx the parse tree
	 */
	void enterFieldList(OberonParser.FieldListContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#fieldList}.
	 * @param ctx the parse tree
	 */
	void exitFieldList(OberonParser.FieldListContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#identList}.
	 * @param ctx the parse tree
	 */
	void enterIdentList(OberonParser.IdentListContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#identList}.
	 * @param ctx the parse tree
	 */
	void exitIdentList(OberonParser.IdentListContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#pointerType}.
	 * @param ctx the parse tree
	 */
	void enterPointerType(OberonParser.PointerTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#pointerType}.
	 * @param ctx the parse tree
	 */
	void exitPointerType(OberonParser.PointerTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#procedureType}.
	 * @param ctx the parse tree
	 */
	void enterProcedureType(OberonParser.ProcedureTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#procedureType}.
	 * @param ctx the parse tree
	 */
	void exitProcedureType(OberonParser.ProcedureTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVariableDeclaration(OberonParser.VariableDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#variableDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVariableDeclaration(OberonParser.VariableDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(OberonParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(OberonParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#relation}.
	 * @param ctx the parse tree
	 */
	void enterRelation(OberonParser.RelationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#relation}.
	 * @param ctx the parse tree
	 */
	void exitRelation(OberonParser.RelationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#simpleExpression}.
	 * @param ctx the parse tree
	 */
	void enterSimpleExpression(OberonParser.SimpleExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#simpleExpression}.
	 * @param ctx the parse tree
	 */
	void exitSimpleExpression(OberonParser.SimpleExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#addOperator}.
	 * @param ctx the parse tree
	 */
	void enterAddOperator(OberonParser.AddOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#addOperator}.
	 * @param ctx the parse tree
	 */
	void exitAddOperator(OberonParser.AddOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(OberonParser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(OberonParser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#mulOperator}.
	 * @param ctx the parse tree
	 */
	void enterMulOperator(OberonParser.MulOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#mulOperator}.
	 * @param ctx the parse tree
	 */
	void exitMulOperator(OberonParser.MulOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(OberonParser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(OberonParser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#designator}.
	 * @param ctx the parse tree
	 */
	void enterDesignator(OberonParser.DesignatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#designator}.
	 * @param ctx the parse tree
	 */
	void exitDesignator(OberonParser.DesignatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#selector}.
	 * @param ctx the parse tree
	 */
	void enterSelector(OberonParser.SelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#selector}.
	 * @param ctx the parse tree
	 */
	void exitSelector(OberonParser.SelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#set}.
	 * @param ctx the parse tree
	 */
	void enterSet(OberonParser.SetContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#set}.
	 * @param ctx the parse tree
	 */
	void exitSet(OberonParser.SetContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#element}.
	 * @param ctx the parse tree
	 */
	void enterElement(OberonParser.ElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#element}.
	 * @param ctx the parse tree
	 */
	void exitElement(OberonParser.ElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#expList}.
	 * @param ctx the parse tree
	 */
	void enterExpList(OberonParser.ExpListContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#expList}.
	 * @param ctx the parse tree
	 */
	void exitExpList(OberonParser.ExpListContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#actualParameters}.
	 * @param ctx the parse tree
	 */
	void enterActualParameters(OberonParser.ActualParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#actualParameters}.
	 * @param ctx the parse tree
	 */
	void exitActualParameters(OberonParser.ActualParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(OberonParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(OberonParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(OberonParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(OberonParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#procedureCall}.
	 * @param ctx the parse tree
	 */
	void enterProcedureCall(OberonParser.ProcedureCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#procedureCall}.
	 * @param ctx the parse tree
	 */
	void exitProcedureCall(OberonParser.ProcedureCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#statementSequence}.
	 * @param ctx the parse tree
	 */
	void enterStatementSequence(OberonParser.StatementSequenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#statementSequence}.
	 * @param ctx the parse tree
	 */
	void exitStatementSequence(OberonParser.StatementSequenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(OberonParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(OberonParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#caseStatement}.
	 * @param ctx the parse tree
	 */
	void enterCaseStatement(OberonParser.CaseStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#caseStatement}.
	 * @param ctx the parse tree
	 */
	void exitCaseStatement(OberonParser.CaseStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#caseItem}.
	 * @param ctx the parse tree
	 */
	void enterCaseItem(OberonParser.CaseItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#caseItem}.
	 * @param ctx the parse tree
	 */
	void exitCaseItem(OberonParser.CaseItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#caseLabelList}.
	 * @param ctx the parse tree
	 */
	void enterCaseLabelList(OberonParser.CaseLabelListContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#caseLabelList}.
	 * @param ctx the parse tree
	 */
	void exitCaseLabelList(OberonParser.CaseLabelListContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#labelRange}.
	 * @param ctx the parse tree
	 */
	void enterLabelRange(OberonParser.LabelRangeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#labelRange}.
	 * @param ctx the parse tree
	 */
	void exitLabelRange(OberonParser.LabelRangeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#label}.
	 * @param ctx the parse tree
	 */
	void enterLabel(OberonParser.LabelContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#label}.
	 * @param ctx the parse tree
	 */
	void exitLabel(OberonParser.LabelContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(OberonParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(OberonParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#repeatStatement}.
	 * @param ctx the parse tree
	 */
	void enterRepeatStatement(OberonParser.RepeatStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#repeatStatement}.
	 * @param ctx the parse tree
	 */
	void exitRepeatStatement(OberonParser.RepeatStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(OberonParser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(OberonParser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#procedureDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterProcedureDeclaration(OberonParser.ProcedureDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#procedureDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitProcedureDeclaration(OberonParser.ProcedureDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#procedureHeading}.
	 * @param ctx the parse tree
	 */
	void enterProcedureHeading(OberonParser.ProcedureHeadingContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#procedureHeading}.
	 * @param ctx the parse tree
	 */
	void exitProcedureHeading(OberonParser.ProcedureHeadingContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#procedureBody}.
	 * @param ctx the parse tree
	 */
	void enterProcedureBody(OberonParser.ProcedureBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#procedureBody}.
	 * @param ctx the parse tree
	 */
	void exitProcedureBody(OberonParser.ProcedureBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#declarationSequence}.
	 * @param ctx the parse tree
	 */
	void enterDeclarationSequence(OberonParser.DeclarationSequenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#declarationSequence}.
	 * @param ctx the parse tree
	 */
	void exitDeclarationSequence(OberonParser.DeclarationSequenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#formalParameters}.
	 * @param ctx the parse tree
	 */
	void enterFormalParameters(OberonParser.FormalParametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#formalParameters}.
	 * @param ctx the parse tree
	 */
	void exitFormalParameters(OberonParser.FormalParametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#fpSection}.
	 * @param ctx the parse tree
	 */
	void enterFpSection(OberonParser.FpSectionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#fpSection}.
	 * @param ctx the parse tree
	 */
	void exitFpSection(OberonParser.FpSectionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#formalType}.
	 * @param ctx the parse tree
	 */
	void enterFormalType(OberonParser.FormalTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#formalType}.
	 * @param ctx the parse tree
	 */
	void exitFormalType(OberonParser.FormalTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#module}.
	 * @param ctx the parse tree
	 */
	void enterModule(OberonParser.ModuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#module}.
	 * @param ctx the parse tree
	 */
	void exitModule(OberonParser.ModuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#importList}.
	 * @param ctx the parse tree
	 */
	void enterImportList(OberonParser.ImportListContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#importList}.
	 * @param ctx the parse tree
	 */
	void exitImportList(OberonParser.ImportListContext ctx);
	/**
	 * Enter a parse tree produced by {@link OberonParser#importItem}.
	 * @param ctx the parse tree
	 */
	void enterImportItem(OberonParser.ImportItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link OberonParser#importItem}.
	 * @param ctx the parse tree
	 */
	void exitImportItem(OberonParser.ImportItemContext ctx);
}