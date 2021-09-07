// qiantang.c �¼���Ǯ��������

#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT	   1
#define STATUS_START	    2
#define STATUS_END	      3

// ��ʼ�����¼�
void create_event()
{
	// ����8�·�18���ǳ�����ǰһ����ʾ
	EVENT_D->at_after(1, -8, -17, -12, STATUS_PROMPT);
}

// ����
private void do_bonus(object room)
{
	object *obs;
	string msg;
	int r;

	obs = all_inventory(room);
	obs = filter_array(obs, (: playerp($1) && living($1) :));
	if (sizeof(obs) < 1)
		return;

	msg = HIC "ֻ����¡¡��һ�������������ˮ��ӿһ����򰶱߾�����\n"
		  "ɲ�Ǽ䣬�������ڣ��������꣬�������ţ������ڣ�����\n"
		  "��������ת�ۣ����Լݳ��硣���������ɽ��˪ѩ�С���\n"
		  "׳�����ƣ�����ν��Զ�������Ὥ�������ģ�����ب��ɽ\n"
		  "����������������һʱ���㲻���������У�������ﶼ��Ȼ\n"
		  "�����ˡ�"NOR"\n";
	message("vision", msg, obs);
	msg = "��˵����ʮ��" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1)
						       : obs->name(1), "��") +
	      "������Ǯ�����۳���";
	CHANNEL_D->do_channel(this_object(), "rumor", msg);

	obs = filter_array(obs, (: $1->query("combat_exp") >= 10000 :));
	if (sizeof(obs) < 1)
		return;

	msg = HIG "��������ӿ�ĳ�ˮ���������򣬶��书�������µ���ᡣ"NOR"\n";
	message("vision", msg, obs);
	obs->add("combat_exp", 1000 + random(500));
	obs->improve_potential(100 + random(100));
	obs->improve_skill("force", 1000 + random(1000), 1);
	MAP_D->record_rumor(obs, "Ǯ��������", this_object());
}

// �¼�����
void trigger_event(int status)
{
	object room;

	room = find_object("/d/hangzhou/qiantang");

	// Ǯ��������
	switch (status)
	{
	case STATUS_PROMPT:
		CHANNEL_D->do_channel(this_object(), "rumor",
			"����ʮ����Ҫ���ˣ���˵������ǰ��Ǯ�����۳���");
		// ����18������
		EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
		break;
		
	case STATUS_START:
		if (objectp(room))
			do_bonus(room);
		// һ��Сʱ�Ժ��䳱
		EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
		break;

	case STATUS_END:
		if (objectp(room))
			message("vision", "��ˮ������������ȥ�������"
					  "�·���������˹�����\n", room);
		// ����ִ��default�е�����

	default:
		create_event();
		break;
	}
}

// ����
string query_detail(string topic)
{
	switch (topic)
	{
	case "Ǯ��������":
		return "ÿ�����ʮ��Ǯ�����ǳ����ǳ�׼ʱ���ʳ�֮Ϊ���š�ÿ�γ�ˮ����"
		       "ʱ������ӿ�����Ʊ��ˣ�ʮ��׳�ۡ�\n";
	}
}
