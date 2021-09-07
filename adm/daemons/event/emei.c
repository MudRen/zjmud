// emei.c �¼������ҽ��ճ�

#include <ansi.h>

void create() { seteuid(getuid()); }

// ��ʼ�����¼�
void create_event()
{
	// ����5�����ճ�
	EVENT_D->at_after(0, 0, 1, -5);
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

	r = random(365);
	if (r == 0)
	{
		msg = HIR "ֻ��̫��һ��һ�������������ٿ����ǰһ����ֻ��һ�����γ������Ƽʣ�\n"
			  "���������ƺ���һ����Ӱ���ڵ��У�����̾�۲��ѡ�"NOR"\n";
		msg += HIG "��ڤڤ�з·�õ��˷�����ָʾ����ʱ��é���ٿ��ĸо���"NOR"\n";
		obs->add("potential", 1000);

		// ���ŵ������ӷ�ѧ����
		foreach (ob in obs)
		{
			if (ob->query("class") != "bonze")
				continue;

			if ((lvl = ob->query_skill("buddhism", 1)) >= 50)
				ob->set_skill("buddhism", lvl + 1);

			if ((lvl = ob->query_skill("mahayana", 1)) >= 50)
				ob->set_skill("mahayana", lvl + 1);

			if ((lvl = ob->query_skill("lamaism", 1)) >= 50)
				ob->set_skill("lamaism", lvl + 1);
		}

		message("vision", msg, obs);

		// ��¼�¼�
		MAP_D->record_rumor(obs, "���ҷ��", this_object());

		CHANNEL_D->do_channel(this_object(), "rumor",
				      "��˵���ҽ𶥷����֣�����̾Ϊ��ֹ����̾���ѡ�");
	} else
	if (r < 250)
	{
		switch (random(3))
		{
		case 0:
			msg = HIY "һ�ֺ���Ծ����ʣ�ӳ��ò��͵��������欣�ãã�ƺ���������ױ��"NOR"\n";
			break;
		case 1:
			msg = HIY "��Ȼ��һ�ֺ���Ծ�����������֮���ʱ�Ի��ޱȣ�ֻ������۾����޷�������"NOR"\n";
			break;
		default:
			msg = HIY "��Ȼ��ǰ������䣬һ�ֺ���ȽȽ����"NOR"\n";
			break;
		}
		msg += HIG "����ͷ����һ����⣬�ƺ��ܵ���ĳ�����ϡ�"NOR"\n";
		obs->improve_potential(10 + random(10));

		message("vision", msg, obs);

		// ��¼�¼�
		MAP_D->record_rumor(obs, "�����ճ�", this_object());
	} else
	{
		switch (random(3))
		{
		case 0:
			msg = WHT "�ۼ�̫���������ʵľ�Ҫ��������ȴ��һƬ����Ʈ�������˸�����ʵʵ��"NOR"\n";
			break;
		case 1:
			msg = WHT "����ǰԽ��Խ���������������أ�����ʲô�����������"NOR"\n";
			break;
		default:
			msg = WHT "��߽����ķ��ף�����һ��һ�����������ͷѹ�ù�âһ˿����������"NOR"\n";
			break;
		}
		msg += HIG "��������̾����̫��ϧ�ˣ���"NOR"\n";

		message("vision", msg, obs);
	}
}

// �¼�����
void trigger_event()
{
	object room;

	// ���ҽ��ճ�
	if (objectp(room = find_object("/d/emei/jinding")))
		do_bonus(room);

	create_event();
}

// ����
string query_detail(string topic)
{
	switch (topic)
	{
	case "���ҷ��":
		return "���ҷ���Ƕ���ɽ���صľ��ۣ�������Զ����ߵĹ�����"
		       "�������Լ�����Ӱ���ǳ������\n";

	case "�����ճ�":
		return "�ڶ���ɽ�������ճ������Ŀ��������������Զ���ɽ����"
		       "�����档\n";
	}
}
