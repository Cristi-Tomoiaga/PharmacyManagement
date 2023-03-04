#include "PrescriptionReadOnlyGUI.h"
#include <QPainter>

void PrescriptionReadOnlyGUI::paintEvent(QPaintEvent* event) {
	QPainter painter{ this };

	for (int i = 0; i < srv.getAllMedicamentsFromPrescription().size(); i++) {
		const int radius = 100;
		int x = radius + rand() % (width() - 2 * radius);
		int y = radius + rand() % (height() - 2 * radius);

		int value = rand();
		if (value % 50 > 45) {
			painter.drawImage(QRect{ x, y, 2 * radius, 2 * radius }, QImage{ "tractor.jpg" }, QRect{ 0, 0, 2560, 1920 });
		}
		else if (value % 50 < 3) {
			painter.setBrush(QBrush{ QImage{ "tractor.jpg" }.scaled(QSize{ radius, radius }, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) });
			painter.drawEllipse(x, y, radius, radius);
		}
		else {
			painter.setBrush(QBrush{ Qt::blue });
			painter.drawEllipse(x, y, radius, radius);
		}
	}
}
