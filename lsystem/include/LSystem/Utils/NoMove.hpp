#pragma once



namespace LSystem
{

	struct NoMove
	{
		NoMove() = default;

		NoMove(NoMove&&) = delete;

		NoMove& operator=(NoMove&&) = delete;

	};

}
