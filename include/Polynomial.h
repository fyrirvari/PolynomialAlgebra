#pragma once
#include "List.h"
#include <cmath>
#include <iostream>
#include <string>

class Monom
{
private:
	double coeff;
	double x_degree;
	double y_degree;
	double z_degree;
public:
	Monom(double coeff = 0, double x_degree = 0, double y_degree = 0, double z_degree = 0)
		: coeff(coeff), x_degree(x_degree), y_degree(y_degree), z_degree(z_degree) {}
	Monom(const Monom& m) : coeff(m.coeff), x_degree(m.x_degree), y_degree(m.y_degree), z_degree(m.z_degree) {}
	~Monom() {}

	inline void set_coeff(double coeff) { this->coeff = coeff; }
	inline void set_x_degree(double x_degree) { this->x_degree = x_degree; }
	inline void set_y_degree(double y_degree) { this->x_degree = y_degree; }
	inline void set_z_degree(double z_degree) { this->x_degree = z_degree; }
	inline double get_coeff() const { return coeff; }
	inline double get_x_degree() const { return x_degree; }
	inline double get_y_degree() const { return y_degree; }
	inline double get_z_degree() const { return z_degree; }

	inline bool exist() { return coeff != 0; }

	Monom& operator=(const Monom& m)
	{
		coeff = m.coeff;
		x_degree = m.x_degree;
		y_degree = m.y_degree;
		z_degree = m.z_degree;
		return *this;
	}

	bool equal_degrees(const Monom& m) const
	{
		if (this != &m)
		{
			if (x_degree != m.x_degree
				|| y_degree != m.y_degree
				|| z_degree != m.z_degree)
				return false;
		}
		return true;
	}

	bool operator==(const Monom& m) const
	{
		if (this != &m)
		{
			if (coeff != m.coeff
				|| x_degree != m.x_degree
				|| y_degree != m.y_degree
				|| z_degree != m.z_degree)
				return false;
		}
		return true;
	}

	bool operator!=(const Monom& m) const
	{
		return !(*this == m);
	}

	friend Monom operator/(const Monom& m1, const Monom& m2)
	{
		return Monom(m1.coeff / m2.coeff, m1.x_degree - m2.x_degree, m1.y_degree - m2.y_degree, m1.z_degree - m2.z_degree);
	}

	friend Monom operator*(const Monom& m1, const Monom& m2)
	{
		return Monom(m1.coeff * m2.coeff, m1.x_degree + m2.x_degree, m1.y_degree + m2.y_degree, m1.z_degree + m2.z_degree);
	}

	friend std::ostream& operator<<(std::ostream& out, const Monom& m)
	{
		out << m.coeff
			<< (m.x_degree != 0 ? "*x^" + std::to_string(m.x_degree) : "")
			<< (m.y_degree != 0 ? "*y^" + std::to_string(m.y_degree) : "")
			<< (m.z_degree != 0 ? "*z^" + std::to_string(m.z_degree) : "");
		return out;
	}

	friend class Polynomial;
};

class Polynomial
{
private:
	List<Monom> monoms;
public:
	Polynomial(const List<Monom>& l = List<Monom>()) : monoms(l) {}
	Polynomial(const Polynomial& p) : monoms(p.monoms) {}
	Polynomial(const Monom& m)
	{
		monoms.push(m);
	}
	~Polynomial() {}

	List<Monom> get_monoms() const { return monoms; }
	void set_monoms(const List<Monom>& l) { monoms = l; }

	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
	{
		Polynomial res(p1);
		for (Monom p2_monom : p2.monoms)
		{
			bool found_such_mon = false;
			for (int j = 0; j < res.monoms.size(); ++j)
			{
				Monom res_monom = res.monoms[j];
				if (res_monom.equal_degrees(p2_monom))
				{
					found_such_mon = true;
					res_monom.set_coeff(res_monom.get_coeff() + p2_monom.get_coeff());
					if (!res_monom.exist())
					{
						res.monoms.erase(j);
						break;
					}
				}
			}
			if (!found_such_mon)
			{
				res.monoms.push(p2_monom);
			}
		}
		return res;
	}

	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
	{
		Polynomial res(p1);
		for (Monom p2_monom : p2.monoms)
		{
			bool found_such_mon = false;
			for (int j = 0; j < res.monoms.size(); ++j)
			{
				Monom res_monom = res.monoms[j];
				if (res_monom.equal_degrees(p2_monom))
				{
					found_such_mon = true;
					res_monom.set_coeff(res_monom.get_coeff() - p2_monom.get_coeff());
					if (!res_monom.exist())
					{
						res.monoms.erase(j);
						break;
					}
				}
			}
			if (!found_such_mon)
			{
				res.monoms.push(p2_monom);
			}
		}
		return res;
	}

	double calculate_value(double x_value, double y_value, double z_value) const
	{
		double sum = 0;
		for (Monom monom : monoms)
			sum += monom.coeff
				* std::pow(x_value, monom.x_degree)
				* std::pow(y_value, monom.y_degree)
				* std::pow(z_value, monom.z_degree);
		return sum;
	}

	Polynomial& operator=(const Polynomial& p)
	{
		if (this != &p)
			monoms = p.monoms;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Polynomial& p)
	{
		for (Monom monom : p.monoms)
		{
			if (monom == p.monoms[0])
				out << monom;
			else
				out << (monom.get_coeff() >= 0 ? "+" : "") << monom;
		}
		return out;
	}
};