#pragma once
#include <vector>
#include <cstdint>
#include <tuple>


class BlockBreaker {
public:
	typedef std::tuple<std::intmax_t, std::intmax_t> Point;//X,Y;
	typedef std::vector<Point> DType;

	bool Initialize(Point Screen_, Point Ball_, Point Bar_, std::size_t BarLength_) {
		Screen = Screen_;
		Bar = Bar_;
		Ball = Ball_;
		BarLength = BarLength_;

		return true;
	}

	bool SetBar(const Point& P) {
		Bar = P;
		return true;
	}
	const Point& GetBar()const  {
		return Bar;
	}
	bool SetBall(const Point& P) {
		Ball = P;
		return true;
	}
	const Point& GetBall()const {
		return Ball;
	}
	bool SetBarLength(std::size_t L) {
		BarLength = L;
	}

	bool SetBallDirection(const Point& Dir) {
		BallDir = Dir;
		return true;
	}

	std::size_t GetBarLength() const {
		return BarLength;
	}
	bool SetBlock(std::uintmax_t X, std::uintmax_t Y) {
		D.push_back({ X,Y });
		return 0;
	}
	const Point& GetBlock(std::size_t Idx) const {
		return D[Idx];
	}

	std::size_t GetBlockCount() const{
		return D.size();
	}

	std::uintmax_t Width() const{
		return std::get<0>(Screen);
	}
	std::uintmax_t Height() const{
		return std::get<1>(Screen);
	}
	/**/
	bool MoveBall() {
		for (std::size_t i = 0; i < BarLength; i++) {
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball) + std::get<1>(BallDir)))) {
				std::get<1>(BallDir) *= -1;
				break;
			}
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball)))) {
				std::get<1>(BallDir) *= -1;
				break;
			}
		}	
		if ((std::get<0>(Ball) + std::get<0>(BallDir)) < 0) {
			std::get<0>(BallDir) *= -1;
		}

		if ((std::get<0>(Ball) + std::get<0>(BallDir)) >= std::get<0>(Screen)) {
			std::get<0>(BallDir) *= -1;
		}

		if ((std::get<1>(Ball) + std::get<1>(BallDir)) >= std::get<1>(Screen)) {
			std::get<1>(BallDir) *= -1;
		}
		
		for (std::size_t i = 0; i < BarLength; i++) {
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball) + std::get<1>(BallDir)))) {
				std::get<1>(BallDir) *= -1;
				break;
			}
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball)))) {
				std::get<0>(BallDir) *= -1;
				break;
			}
		}


		for (std::size_t i = 0; i < D.size(); i++) {

			if ((std::get<0>(D[i]) == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(D[i]) == std::get<1>(Ball))) {
				D.erase(D.begin() + i);
				std::get<0>(BallDir) *= -1;	
				break;
			}
			if ((std::get<0>(D[i]) == (std::get<0>(Ball))) && (std::get<1>(D[i]) == std::get<1>(Ball) + std::get<1>(BallDir))) {
				D.erase(D.begin() + i);
				std::get<1>(BallDir) *= -1;
				break;
			}
			if (std::get<0>(D[i]) == (std::get<0>(Ball) + std::get<0>(BallDir)) && std::get<1>(D[i]) == (std::get<1>(Ball) + std::get<1>(BallDir))) {
				D.erase(D.begin() + i);
				std::get<0>(BallDir) *= -1;	
				std::get<1>(BallDir) *= -1;	
				break;
			}
		}


		std::get<0>(Ball) += std::get<0>(BallDir);
		std::get<1>(Ball) += std::get<1>(BallDir);

		return true;
	}
/**/
/** /
	bool MoveBall() {

		for (std::size_t i = 0; i < D.size(); i++) {

			if ((std::get<0>(D[i]) == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(D[i]) == std::get<1>(Ball))) {
				D.erase(D.begin() + i);
				std::get<0>(BallDir) *= -1;	
				return true;
			}
			if ((std::get<0>(D[i]) == (std::get<0>(Ball))) && (std::get<1>(D[i]) == std::get<1>(Ball)+ std::get<1>(BallDir))) {
				D.erase(D.begin() + i);
				std::get<1>(BallDir) *= -1;	
				return true;
			}
			if (std::get<0>(D[i]) == (std::get<0>(Ball) + std::get<0>(BallDir)) && std::get<1>(D[i]) == (std::get<1>(Ball) + std::get<1>(BallDir))) {
				D.erase(D.begin() + i);
				std::get<0>(BallDir) *= -1;	
				std::get<1>(BallDir) *= -1;	
				return true;
			}
		}
		for (std::size_t i = 0; i < BarLength; i++) {
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball) + std::get<1>(BallDir)))) {
				std::get<1>(BallDir) *= -1;
				return true;
			}
			if ((std::get<0>(Bar) + i == (std::get<0>(Ball) + std::get<0>(BallDir))) && (std::get<1>(Bar) == (std::get<1>(Ball)))) {
				std::get<1>(BallDir) *= -1;
				return true;
			}
		}

		if ((std::get<0>(Ball) + std::get<0>(BallDir)) < 0) {
			std::get<0>(BallDir) *= -1;
		}

		if ((std::get<0>(Ball) + std::get<0>(BallDir)) >= std::get<0>(Screen)) {
			std::get<0>(BallDir) *= -1;
		}

		if ((std::get<1>(Ball) + std::get<1>(BallDir)) >= std::get<1>(Screen)) {
			std::get<1>(BallDir) *= -1;
		}
		std::get<0>(Ball) += std::get<0>(BallDir);
		std::get<1>(Ball) += std::get<1>(BallDir);

		return true;
	}
/**/
	bool MoveBarLeft() {
		if (std::get<0>(Bar)-1 < 0) { return false; }
		std::get<0>(Bar)--;
		return true;
	}
	bool MoveBarRight() {
		if (std::get<0>(Bar)+BarLength >= std::get<0>(Screen)) { return false; }
		std::get<0>(Bar)++;
		return true;
	}
	bool MoveBarDown() {
		if (std::get<1>(Bar) - 1 < 0) { return false; }
		std::get<1>(Bar)--;
		return true;
	}
	bool MoveBarUp() {
		if (std::get<1>(Bar)+1 >= std::get<1>(Screen)) { return false; }
		std::get<1>(Bar)++;
		return true;
	}
	bool IsEnd() {
		if (D.size() == 0) { return true; }
		return std::get<1>(Ball) == 0 ? true : false;
	}

protected:
	DType D;
	Point Screen;
	Point Bar;
	std::uintmax_t BarLength = 3;
	Point Ball;
	Point BallDir{1,1};
};