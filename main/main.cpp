#include				"Logger.hpp"
#include				"ImageLoader.hpp"
#include				"SkyboxLoader.hpp"
#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"
#include				<exception>

#include				"EntityManager.hpp"
#include				"ComponentManager.hpp"
#include				"SystemManager.hpp"

#include				"Systems.hpp"

#include				"Components.hpp"

static Camera<Orthographic, FlatCamera> camera;
// static Camera<Perspective, FreeFly> camera;

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  static double				fps = 0;
  static int				frames_done = 0;
  static double				old_time = al_get_time();

  camera.update(time, ev);
  SystemManager::getInstance().draw(time, ev);

  if(time - old_time >= 1.0)
    {
      fps = frames_done / (time - old_time);
      frames_done = 0;
      old_time = time;
      std::cout << "FPS : " << fps << " || TIME : " << old_time << std::endl;
    }
  frames_done++;
}

void					update(float time, const ALLEGRO_EVENT &ev)
{
  SystemManager::getInstance().update(time, ev);
}


void					key(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);

  (void)time;
}

int					main()
{

  ////////////////////
  // initialisation //
  ////////////////////

  if (!MainManager::getInstance().init())
    return 0;
  if (!MainManager::getInstance().launch(1344, 704))
    return 0;

  //////////
  // main //
  //////////

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
  MediaManager::getInstance().registerLoader(new SkyboxLoader, ".skybox");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setKeyLoop(key);
  EventManager::getInstance().setUpdateLoop(update);

  if (!camera.init())
    return 0;

  SystemManager::getInstance().add<WaterPhysicsSystem>(0);
  SystemManager::getInstance().add<WaterRenderSystem>(10, true);

  unsigned int e = EntityManager::getInstance().newEntity();
  WaterBox &wb = ComponentManager::getInstance().addComponent<WaterBox>(e);

  wb.set(glm::vec2(30.0f, 30.0f), glm::vec2(500.0f, 300.0f), 300);
  wb.setPhysics(glm::vec2(0.0f, -10.0f), 2.0f);
  (void)wb;

  try
    {
      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}
