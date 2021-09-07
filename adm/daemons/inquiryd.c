// inquiryd.c

#include <ansi.h>

int parse_inquiry(object me, object ob, string topic)
{
	switch (topic)
	{
	case "name":
		message_vision( CYN "$N��$n�ʵ�������" + RANK_D->query_respect(ob)
			+ "���մ�����"NOR"\n", me, ob);
		return 1;

	case "here":
		message_vision(CYN "$N��$n�ʵ�����λ" + RANK_D->query_respect(ob)
			+ "��" + RANK_D->query_self(me) +
			"�����󱦵أ���֪������Щʲ��������飿"NOR"\n",
			me, ob);
		return 1;

	case "rumors":
	case "��Ϣ":
		message_vision(CYN "$N��$n�ʵ�����λ" + RANK_D->query_respect(ob)
			+ "����֪�����û����˵ʲô��Ϣ��"NOR"\n", me, ob);
		return 1;

	default:
		return 0;
	}
}
