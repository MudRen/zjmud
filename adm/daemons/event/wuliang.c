// wuliang.c �¼�������ɽ��ڽ���

#include <ansi.h>

void create() { seteuid(getuid()); }

// ��ʼ�����¼�
void create_event()
{
	// ÿ��15���賿
	EVENT_D->at_after(0, 1, -15, -23);
}

// ����
private void do_bonus(object room)
{
	object *obs;
	object ob;
	string msg;
	int lvl;
	int r;

	obs = all_inventory(room);
	obs = filter_array(obs, (: playerp($1) && living($1) :));
	if (sizeof(obs) < 1)
		return;

	r = random(100);
	if (r == 0)
	{
		msg = HIW  "ֻ������¹��£�����Ʈ�ݾ��׵���Ӱ��ӳ�ڶ���ɽ��֮�ϣ��ֽ�������\n"
			   "�裬����ٴ죬��Ӱ���衣�㲻�ɾ�̾�����֮�У�������˾���֮������\n"
			   "����Ե�ü�����֮�ˣ�ʵ���Ǹ��ַ�ǳ��"NOR"\n";

		message("vision", msg, obs);

		obs->add("potential", 1000);
		obs->add("combat_exp", 5000);

		// ������ѧ��������������������
		foreach (ob in obs)
		{
			if (ob->query("combat_exp") > 2000000)
			{
				tell_object(ob, HIG "�����а��Ե���������˵�����"
						"���ϸ��֣������Լ��ƺ�Ҳ�ɰ쵽��"NOR"\n");
				continue;
			}

			if ((lvl = ob->query_skill("sword", 1)) >= 80 &&
			    ob->can_improve_skill("sword"))
				ob->improve_skill("sword", 90000);

			if ((lvl = ob->query_skill("dodge", 1)) >= 80 &&
			    ob->can_improve_skill("dodge"))
				ob->improve_skill("dodge", 90000);

			if ((lvl = ob->query_skill("martial-cognize", 1)) >= 80 &&
			    ob->can_improve_skill("martial-cognize"))
				ob->improve_skill("martial-cognize", 40000);

			tell_object(ob, HIG "������˵Ľ����������У���ѧ�϶�ʱ�����µ�����"NOR"\n");
		}

		// ��¼�¼�
		MAP_D->record_rumor(obs, "����ɽ��ڽ���", this_object());

		CHANNEL_D->do_channel(this_object(), "rumor",
				      "��˵��������ɽ�ֳ����˽��裬��Ӱ���棬���˷�����˼��");
	} else
	if (r < 60)
	{
		switch (random(3))
		{
		case 0:
			msg = HIY "ֻ����������ɽ�������Ӱһ������������֮���ݣ���������޷���׽��"NOR"\n";
			break;
		case 1:
			msg = HIY "ֻ������ɽ���������������Ӱ���ƺ���ʩչһ�������ޱȵ��书��ѧ��"NOR"\n";
			break;
		default:
			msg = HIY "��Ȼ������Ʈ�ݾ��׵���Ӱ��ӳ�ڶ���ɽ�ϣ�����Ӱת˲���ţ�������޷����塣"NOR"\n";
			break;
		}
		msg += HIG "���ܵ�����Ӱ�ĸ�����ѧ����������һЩ��ᡣ"NOR"\n";
		obs->improve_experience(500 + random(500));

		message("vision", msg, obs);

		// ��¼�¼�
		MAP_D->record_rumor(obs, "����ɽ�����Ӱ", this_object());
	} else
	{
		switch (random(3))
		{
		case 0:
			msg = WHT "�ۼ�����¹����𣬿���һ����Ʈ�����ڸ����¹⣬����ǰ��ʱһƬ��ڡ�"NOR"\n";
			break;
		case 1:
			msg = WHT "��Ŀ��ת����ע���Ŷ������ڣ���ɲ�Ǽ�����������ɽ����ƣ����¹����˸���ʵ��"NOR"\n";
			break;
		default:
			msg = WHT "ҹ����������һ����Ũ����Ʋ�ȴ��������գ����������ɽͷ���޷����塣"NOR"\n";
			break;
		}
		msg += HIG "�㲻��̾Ϣ����������Ե��δ������Ե������Ӱ����"NOR"\n";

		message("vision", msg, obs);
	}
}

// �¼�����
void trigger_event()
{
	object room;

	// ����ɽ��ڽ���
	if (objectp(room = find_object("/d/wanjiegu/wlhoushan")))
		do_bonus(room);

	create_event();
}

// ����
string query_detail(string topic)
{
	switch (topic)
	{
	case "����ɽ��ڽ���":
		return "����¹��£�����ɽ����������ƫƫ���裬������̬"
		       "ƽ���ѵ�һ����\n";

	case "����ɽ�����Ӱ":
		return "����¹��£�����������ԼԼ��Ӱ������֮�ˡ�ʵ��"
		       "������С�\n";

	}
}
