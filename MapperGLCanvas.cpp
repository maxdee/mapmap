/*
 * MapperGLCanvas.cpp
 *
 * (c) 2013 Sofian Audry -- info(@)sofianaudry(.)com
 * (c) 2013 Alexandre Quessy -- alexandre(@)quessy(.)net
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MapperGLCanvas.h"

#include "MainWindow.h"

MapperGLCanvas::MapperGLCanvas(QWidget* parent, const QGLWidget * shareWidget)
  : QGLWidget(parent, shareWidget), _mousepressed(false), _active_vertex(NO_VERTEX)
{
}

void MapperGLCanvas::initializeGL()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  //qglClearColor(Qt::black);
  //glShadeModel(GL_FLAT);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
}

void MapperGLCanvas::resizeGL(int /* width */, int /* height */)
{
  glViewport(0, 0, width(), height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (
    0.0f, (GLfloat) width(), // left, right
    (GLfloat) height(), 0.0f, // bottom, top
    -1.0, 1.0f);
  glMatrixMode (GL_MODELVIEW);

//  glClearColor(0.0, 0.0, 0.0, 0.0);
//
//  glViewport(0, 0, width, height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glMatrixMode (GL_PROJECTION);
//  glLoadIdentity ();
//  glOrtho (
//    0.0f, (GLfloat) width, // left, right
//    (GLfloat) height, 0.0f, // bottom, top
//    -1.0, 1.0f);
//  glMatrixMode (GL_MODELVIEW);
}

void MapperGLCanvas::paintGL()
{
}

void MapperGLCanvas::draw(QPainter* painter)
{
  enterDraw(painter);
  doDraw(painter);
  exitDraw(painter);
}

void MapperGLCanvas::enterDraw(QPainter* painter)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  Q_UNUSED(painter);

//  glClearColor(0.0, 0.0, 0.0, 0.0);
//  glClear(GL_COLOR_BUFFER_BIT);
//  glViewport(0, 0, (GLint) GetSize().x, (GLint) GetSize().y);

//  glMatrixMode (GL_PROJECTION);
//  glLoadIdentity ();
//  glOrtho (
//    0.0f, (float) GetSize().x, // left, right
//    (float) GetSize().y, 0.0f, // bottom, top
//    -1.0, 1.0f);
//  glMatrixMode (GL_MODELVIEW);

////  glLoadIdentity (); // FIXME? is this needed here?
}

Shape* MapperGLCanvas::getCurrentShape()
{
  return getShapeFromMappingId(MainWindow::getInstance().getCurrentMappingId());
}

void MapperGLCanvas::mousePressEvent(QMouseEvent* event)
{
  int i, dist, maxdist, mindist;
  int xmouse = event->x();
  int ymouse = event->y();
  maxdist = mindist = 50;
  if (event->buttons() & Qt::LeftButton)
  {
    Shape* shape = getCurrentShape();
    if (shape)
    {
      for (i = 0; i < shape->nVertices(); i++)
      {
        Point *p = shape->getVertex(i);
        dist = abs(xmouse - p->x()) + abs(ymouse - p->y());
        if (dist < maxdist && dist < mindist)
        {
          _active_vertex = i;
          mindist = dist;
        }
      }
      _mousepressed = true;
    }
  }
  if (event->buttons() & Qt::RightButton)
  {
    Shape* shape = getCurrentShape();
    if (shape->includesPoint(xmouse, ymouse))
    {
      _shapegrabbed = true;
      _shapefirstgrab = true;
    }
  }
}

void MapperGLCanvas::mouseReleaseEvent(QMouseEvent* event)
{
  Q_UNUSED(event);
  // std::cout << "Mouse Release event " << std::endl;
  _mousepressed = false;
  _shapegrabbed = false;
}

void MapperGLCanvas::mouseMoveEvent(QMouseEvent* event)
{

  if (_mousepressed)
  {
    // std::cout << "Move event " << std::endl;
    Shape* shape = getCurrentShape();
    if (shape && _active_vertex != NO_VERTEX)
    {
      Point *p = shape->getVertex(_active_vertex);
      p->setX(event->x());
      p->setY(event->y());

      glueVertex(shape, p);
      shape->setVertex(_active_vertex, *p);

      update();
      emit shapeChanged(getCurrentShape());
    }
  }
  else if (_shapegrabbed)
  {
    // std::cout << "Move event " << std::endl;
    Shape* shape = getCurrentShape();
    static Point p(0,0);
    if (shape)
    {
      if (_shapefirstgrab == false)
      {    
        shape->translate(event->x() - p.x(), event->y() - p.y());
        update();
        emit shapeChanged(getCurrentShape());
      }  
      else
        _shapefirstgrab = false;
    }
    p.setX( event->x() );
    p.setY( event->y() );

  }
}

void MapperGLCanvas::keyPressEvent(QKeyEvent* event)
{
  Q_UNUSED(event);
//  std::cout << "Key pressed" << std::endl;
//  int xMove = 0;
//  int yMove = 0;
//  switch (event->key()) {
//  case Qt::Key_Tab:
//    if (event->modifiers() & Qt::ControlModifier)
//      switchImage( (Common::getCurrentSourceId() + 1) % Common::nImages());
//    else
//    {
//      Quad& quad = getQuad();
//      _active_vertex = (_active_vertex + 1 ) % 4;
//    }
//    break;
//  case Qt::Key_Up:
//    yMove = -1;
//    break;
//  case Qt::Key_Down:
//    yMove = +1;
//    break;
//  case Qt::Key_Left:
//    xMove = -1;
//    break;
//  case Qt::Key_Right:
//    xMove = +1;
//    break;
//  default:
//    std::cerr << "Unhandled key" << std::endl;
//    QWidget::keyPressEvent(event);
//    break;
//  }
//
//  Quad& quad = getQuad();
//  Point *p = quad.getVertex(_active_vertex);
//  p->x += xMove;
//  p->y += yMove;
//  quad.setVertex(_active_vertex, p);
//
//  update();
//
//  emit quadChanged();
}

void MapperGLCanvas::paintEvent(QPaintEvent* /* event */)
{
  makeCurrent();

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  draw(&painter);

  painter.end();
//  updateGL();
}

//void MapperGLCanvas::switchImage(int imageId)
//{
//  MainWindow::getInstance().setCurrentPaint(imageId);
//  emit imageChanged();
//}

//QSize MapperGLCanvas::sizeHint() const
//{
//  return QSize( 640, 480 );
//}
//
//QSize MapperGLCanvas::minimumSizeHint() const
//{
//  return QSize( 320, 240 );
//}

void MapperGLCanvas::exitDraw(QPainter* painter)
{
  Q_UNUSED(painter);
//  glFlush();
//  swapBuffers();
}

void MapperGLCanvas::updateCanvas()
{
  update();
}

/* Stick vertex p of Shape orig to another Shape's vertex, if the 2 vertices are
 * close enough. The distance per coordinate is currently set in dist_stick
 * variable. Perhaps the sticky-sensitivity should be configurable through GUI */
void MapperGLCanvas::glueVertex(Shape *orig, Point *p)
{
  MappingManager m = MainWindow::getInstance().getMappingManager();
  int dist_stick = 10; /*this parameter may*/
  for (int mappingId = 0; mappingId < m.nMappings(); mappingId++)
  {
    Shape *shape = getShapeFromMappingId(mappingId);
    if (shape != orig)
    {
      for (int vertex = 0; vertex < shape->nVertices(); vertex++)
      {
        Point *v = shape->getVertex(vertex);
        if ((abs(v->x() - p->x()) < dist_stick) &&
            (abs(v->y() - p->y()) < dist_stick))
        {
          p->setX(v->x());
          p->setY(v->y());
        }
      }
    }
  }  
}

void MapperGLCanvas::deselectAll()
{
  _active_vertex = NO_VERTEX;
  _shapegrabbed = false;
  _shapefirstgrab = false;
  _mousepressed = false;
}
