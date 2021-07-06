#pragma once

#include <QObject>

#include <LSystem/Plant.hpp>
#include <LSystem/OperationDatabase.hpp>



class ModelController : public QObject
{
	Q_OBJECT

public:

	ModelController();


private:

	LSystem::Plant m_plant;
	LSystem::OperationDatabase m_operation_database;

};

