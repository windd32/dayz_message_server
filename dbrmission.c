//Готовый код обработки !hop
//Файл: scripts/5_Mission/YourModMission.c
//Как это работает?
//Перехватывает события чата (OnEvent)
//Проверяет, является ли сообщение командой !hop
//message.IndexOf("!hop") == 0 проверяет, начинается ли строка с !hop.
//Отправляет ответ игроку (SendReply)
//Находит игрока по имени
//Использует RPC для отправки сообщения в чат

modded class MissionServer
{
    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        // Проверяем, является ли событие сообщением в чате
        if (eventTypeId == ChatMessageEventTypeID)
        {
            ChatMessageEventParams chatParams;
            if (Class.CastTo(chatParams, params))
            {
                string message = chatParams.param3;
                string sender = chatParams.param2;  // Имя отправителя

                // Проверяем, содержит ли сообщение команду "!hop"
                if (message.IndexOf("!hop") == 0)  // Проверяем, начинается ли сообщение с "!hop"
                {
                    SendReply(sender, "Вы вызвали команду !hop.");
                    
                    // Здесь можно добавить логику переключения сервера или телепортации
                }
            }
        }
    }

    void SendReply(string playerName, string text)
    {
        PlayerBase player = GetPlayerByName(playerName);
        if (player)
        {
            Param1<string> messageParam = new Param1<string>(text);
            GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, messageParam, true, player.GetIdentity());
        }
    }

    PlayerBase GetPlayerByName(string name)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            PlayerBase pb = PlayerBase.Cast(player);
            if (pb && pb.GetIdentity() && pb.GetIdentity().GetName() == name)
            {
                return pb;
            }
        }
        return null;
    }
}
