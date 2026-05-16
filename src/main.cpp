#include <Geode/modify/MenuLayer.hpp>
#include <undefined0.3d-api/include/3DAPI.hpp>

class $modify(HookedMenuLayer, MenuLayer) {
    struct Fields {
        ThreeDeeAPI::ThirdDimensionObject* m_teapot;
    };

    bool init() {
        if (!MenuLayer::init()) return false;

        auto fields = m_fields.self();

        auto wrapper = ThreeDeeAPI::ThirdDimensionNode::create();
        fields->m_teapot = ThreeDeeAPI::ThirdDimensionObject::create();
        auto res = fields->m_teapot->loadObject("cube.obj"_spr, false);
        if (!res) {
            geode::log::error("failed to load: {}", res.unwrapErr());
            return true;
        }

        this->addChild(wrapper);
        wrapper->addChild(fields->m_teapot);

        wrapper->setCameraPosition({ -.7f, 0.f, 0.f });
        wrapper->setCameraAim({ 10.f, 0.f, 0.f });
        wrapper->setCameraFOV(120.f);

        wrapper->setZOrder(-1);

        wrapper->setPosition(cocos2d::CCDirector::get()->getWinSize() / 2.f);

        fields->m_teapot->setRotationX(90.f);
        fields->m_teapot->setRotationZ(60.f);

        this->schedule(schedule_selector(HookedMenuLayer::shit), 0.f);

        m_menuGameLayer->setZOrder(-5); // get back there

        return true;
    }

    void shit(float dt) {
        m_fields->m_teapot->setRotationX(m_fields->m_teapot->getRotationX() + dt*10.f);
        m_fields->m_teapot->setRotationY(m_fields->m_teapot->getRotationY() + dt*10.f);
        m_fields->m_teapot->setRotationZ(m_fields->m_teapot->getRotationZ() + dt*10.f);
    }
};
