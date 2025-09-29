#include "EventInitializer.h"
#include "system_EventBus.h"
#include "EventStructs.h"
#include "loader_Sound.h"
#include "DxLib.h"
#include "GameObjectRequestAdd.h"
#include"TimedText.h"
#include"GameObject.h"
#include "text.h"

void EventInitializer::LevelUp()
{
	// レベルアップイベントの購読
	EventBus::Instance().Subscribe<LevelUpEvent>(
		[](const LevelUpEvent& e) {
			auto soundRes = SoundLoader::Instance().LoadSound("data/sound/level/levelUp.MP3");
			if (soundRes) {
				PlaySoundMem(soundRes->GetHandle(), DX_PLAYTYPE_BACK);
			}
		});

}

void EventInitializer::ScreenTextMessage()
{
	//	時間制限付きの表示
	EventBus::Instance().Subscribe<TimedMessageRenderEvent>(
		[](const TimedMessageRenderEvent& e)
		{
			if (e.messages.empty()) return;

			//	インスタンスの生成
			auto obj = std::make_shared<GameObject>();

			//	表示コンポーネントの追加
			obj->AddComponent<TextTimed>(e.messages, e.position, e.displayTime, e.color);

			//	インスタンスをコレクションに追加
			GameObjectQueue::Instance().Enqueue(obj);
		}
	);

	EventBus::Instance().Subscribe<MessageRenderEvent>(
		[](const MessageRenderEvent& e) {
			if (e.messages.empty()) return;

			auto obj = std::make_shared<GameObject>();
			obj->AddComponent<Text>(e.messages, e.color,true,e.size);
			GameObjectQueue::Instance().Enqueue(obj);

		}
	);

	//	時間制限なしの表示

}

void EventInitializer::InitializeEvents()
{
	LevelUp();	//	レベルアップ音
	ScreenTextMessage();	//	文字列の表示
}
