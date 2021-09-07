// emei.c �¼�������ɽ���ҹ��

#include <ansi.h>

void create() { seteuid(getuid()); }

// ��ʼ�����¼�
void create_event()
{
	// ÿ�賿12��
	EVENT_D->at_after(0, 0, 1, -1);
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
		msg = HIR "ֻ�������Ȼ����һ��̶���Ħ�������������ϲԣ����������ѻ�Ȼ����\n"
			  "���������ǡ�ҹ�������׹����â���գ����������֮�У����ټ��������\n"
			  "ɫ���Σ����ҹ񷾹�������һ�㡣�㲻����̾������Ȼ֮�����������Ī\n"
			  "�⡣"NOR"\n";

		msg += HIC "����ϸ�Ĺ۲����������ȫ���̣��������о��кܶ���ؿ���������ѧ��"NOR"\n";
		obs->add("potential", 300);
		obs->add("combat_exp", 500);

		message("vision", msg, obs);

		// ���ӻ����������������ҵ��ӿ���ͬʱ�����ڹ���������
		foreach (ob in obs)
		{
			if ((lvl = ob->query_skill("dodge", 1)) >= 80 &&
			    ob->can_improve_skill("dodge"))
				ob->improve_skill("dodge", 160000);

			if ((lvl = ob->query_skill("throwing", 1)) >= 80 &&
			    ob->can_improve_skill("throwing"))
				ob->improve_skill("throwing", 160000);

			if (ob->query("born_family") != "�������")
				continue;

			if (ob->query_skill("mantian-xing", 1) >= 80 &&
			    ! ob->query("can_perform/mantian-xing/xing"))
			{
				tell_object(ob, HIM "������һ������ʱ������������������������������һ������"NOR"\n");
				ob->set("can_perform/mantian-xing/xing", 1);
			}
		}

		// ��¼�¼�
		MAP_D->record_rumor(obs, "���������", this_object());

		CHANNEL_D->do_channel(this_object(), "rumor",
				      "��˵����ɽ�����ҹ�վ��������꣬����ͷף�ɷΪ׳�ۡ�");
	} else
	if (r < 40)
	{
		msg = RED "ֻ��Զ��һ��̶���Ħ��������Ŀ��ȥ�����־������Ǵ���߻��������ξ�\n"
			  "��ίʵ̫Զ�������޷����塣"NOR"\n";

		msg += HIC "��۰����ǣ������Ķ԰�����������һ˿��ᡣ"NOR"\n";

		obs->improve_skill("throwing", 300);
		message("vision", msg, obs);

		// ��¼�¼�
		MAP_D->record_rumor(obs, "ҹ������", this_object());
	} else
	{
		switch (random(2))
		{
		case 0:
			msg = WHT "�ۼ����һƬ������֪�������꽫���������μ��ң���Ʋ��ȴ��Ե�ü���"NOR"\n";
			break;
		default:
			msg = WHT "�ۼ����һƬ����������ˮ�����������Ʋ㽻�ӣ�����ʲô�����������"NOR"\n";
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

	// ����ɽ���ҹ��
	if (objectp(room = find_object("/d/guanwai/tianchi1")))
		do_bonus(room);

	create_event();
}

// ����
string query_detail(string topic)
{
	switch (topic)
	{
	case "���������":
		return "����ɽ���ҹ���ܼ������꣬ɷΪ׳�ۡ�\n";

	case "ҹ������":
		return "ҹ�ճ����������䣬��Ϊ������\n";
	}
}
