// renter.c ����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define GUARD_CMD       "/cmds/std/guard"

mixed ask_rent();
mixed try_to_hire(object me, object ob);
void hire(object helper, object owner);
void create_all_helper();

mapping *info = ({
// level 1
([      "life"  : 500,
	"neili" : 800,
	"cost"  : 10,
]),
// level 2
([      "life"  : 800,
	"neili" : 1000,
	"cost"  : 20,
]),
// level 3
([      "life"  : 1000,
	"neili" : 1200,
	"cost"  : 25,
]),
// level 4
([      "life"  : 1200,
	"neili" : 1600,
	"cost"  : 30,
]),
// level 5
([      "life"  : 1500,
	"neili" : 2000,
	"cost"  : 35,
]),
// level 6
([      "life"  : 2000,
	"neili" : 2500,
	"cost"  : 40,
]),
// level 7
([      "life"  : 2500,
	"neili" : 3000,
	"cost"  : 50,
]),
// level 8
([      "life"  : 3000,
	"neili" : 3500,
	"cost"  : 60,
]),
// level 9
([      "life"  : 3500,
	"neili" : 4000,
	"cost"  : 80,
]),
// level 10
([      "life"  : 4000,
	"neili" : 5000,
	"cost"  : 100,
]),
// level 11
([      "life"  : 4500,
	"neili" : 6000,
	"cost"  : 150,
]),
// level 12
([      "life"  : 5000,
	"neili" : 7000,
	"cost"  : 200,
]),
// level 13
([      "life"  : 6000,
	"neili" : 8000,
	"cost"  : 300,
]),
// level 14
([      "life"  : 7000,
	"neili" : 9000,
	"cost"  : 500,
]),
// level 15
([      "life"  : 8000,
	"neili" : 9999,
	"cost"  : 700,
]),
});

void create()
{
	set_name("����ʹ��", ({ "xiake dizi", "dizi", "renter" }));
	set("long", "�����Ż����������������ƺ������书��\n");

	set("gender", "����");
	set("age", 25);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set("inquiry", ([
		"ͬ��" : (: ask_rent :), 
		"ʦ��" : (: ask_rent :), 
		"rent" : (: ask_rent :), 
	]));

	create_family("���͵�", 0, "����");
	setup();
	carry_object("/clone/misc/cloth")->wear();

	call_out("create_all_helper", 0);
}

mixed ask_rent()
{
	object me;
	object *obs;
	string msg;
	string fam;
	int i;

	me = this_player();
	if (arrayp(obs = me->query_temp("hire")))
	{
		obs -= ({ 0 });
		fam = query("family/family_name");
		obs = filter_array(obs, (: $1->query("family/family_name") == $(fam) :));
		if (sizeof(obs))
			return "���ڲ�����" + obs[0]->name() + "������һ��ô���㻹����ô����";
	}

	obs = query_temp("helpers");
	if (! arrayp(obs) || (obs = obs - ({ 0 }),sizeof(obs) < 1))
		return "�ҵ�ʦ�ֵܶ��������㻹�ǵ����������ɡ�";

	msg = "$NЦ��Ц����������������ߵ�ʦ�ֵ�����ô�������㿴���ɡ���\n";
	for (i = 0; i < sizeof(obs); i++)
		msg += sprintf("%2d. %-27s  �ȼ���%d\n",
			       i + 1,
			       obs[i]->name(1) + "(" + obs[i]->query("id") + ")",
			       obs[i]->query("npc_level"));
	switch (random(5))
	{
	case 0:
		msg += "$N���˿�$n��������������˭�����æ����������˵˵����\n";
		break;
	case 1:
		msg += "$N��$n�������ҵ�ʦ�ֵ�ˮƽ���и��£�����һ���ɵ����ó��İɣ���\n";
		break;
	case 2:
		msg += "$N΢΢һЦ����$n�����������˭���ʣ���\n";
		break;
	}
	message_vision(msg, this_object(), me);
	return 1;
}

int accept_object(object me, object ob)
{
	object helper;
	object *obs;
	int cost;
	int n;

	if (! ob->query("money_id"))
		return 0;

	if (! objectp(helper = me->query_temp("pending/rent/helper")))
	{
		command("say �����Ǯ��ʲô�������������͵�ô��");
		return 0;
	}

	cost = me->query_temp("pending/rent/cost");
	n = ob->value() / 10000;
	if (n < cost)
	{
		command("say ��������ɲ��ܴ��ۣ��㻹�����˰ɣ�");
		if (n * 2 >= cost && me->query("special_skill/treat"))
			message_vision("$N���ڵ��ϣ�����$n���޺���������Ϳ��������������ɣ���\n"
						"$n���ˣ���Ϊ���Σ�ҡҡͷ��̾�����������ðɺðɣ����ˡ���\n", me, this_object());
		else
			return 0;
	}

	message_vision("$n�ӹ�$N�ݹ�����" + ob->name() + "���������ϣ��е������Ȼ������\n",me, this_object());
	destruct(ob);
	message_vision("$N������������" + helper->name() + "������������������Ǯ�������ˣ���\n", this_object());
	helper->move(environment());
	message_vision("$n���˹��������˿�$N��\n", me, helper);
	command("say ������" + helper->name() + "��������λ" +	RANK_D->query_respect(me) + "����һͬȥ�ɡ�");
	message_vision("$n���ͷ����$N�������䣬������$P�����\n",me, helper);

	// ��ʼ����Ӷ����
	// ���ù�Ӷ��ʼ��ʱ�䣬���ˣ�ȥ��Ŀǰ�����ڹ�Ӷ��״
	// ̬���������ˣ���ʼ��ά��������
	helper->set_temp("help_time", time());
	helper->set_temp("owner", me);
	helper->set_temp("owner_name", me->name(1));
	helper->set_temp("owner_id", me->query("id"));
	helper->delete_temp("renter");
	helper->set_leader(me);
	helper->keep_heart_beat();

	// �������˵���Ϣ
	obs = me->query_temp("hire");
	if (arrayp(obs))
	{
		obs -= ({ 0 });
		obs += ({ helper });
	} else
		obs = ({ helper });
	me->set_temp("hire", obs);

	GUARD_CMD->main(helper, me);
	me->delete_temp("pending/rent");

	obs = query_temp("helpers");

	if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });

	obs -= ({ helper });

	set_temp("helpers", obs);

	CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "���Ϻ����뵽��һ�����͵����ӡ�");
	return -1;
}

mixed accept_ask(object me, string topic)
{
	object ob;
	object *obs;

	obs = query_temp("helpers");
	if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });

	foreach (ob in obs)
		if (ob->id(topic) || ob->name(1) == topic)
			return try_to_hire(me, ob);

	message_vision(CYN "$N" CYN "���˿�$n" CYN "�����ʵ����������ʲô����Ҫ���ҵ�" HIY "ͬ��"NOR CYN "ʦ�ֵ�ô����"NOR"\n",this_object(), me);
	return 1;
}

mixed try_to_hire(object me, object ob)
{
	object *obs;
	string fam;
	int cost;

	if (me->query("weiwang") < 1000)
		return "�������ͷҲ��ʹ���ˣ����˰ɣ�"; 

	if (me->query("score") < 10000)
		return "�㽭������̫ǳ���������ˡ�"; 

	if (me->query("combat_exp") < 50000) 
		return "����书̫���֧ʹ˭ѽ��"; 

	if (me->query("combat/DPS") > 30)
		return "�����ˣ�����̫�࣬�������͵��ĵ��ӿɲ�������ΪŰ��";

	if (me->query("combat/WPK") > 30)
		return "������ѽ���������飬ɱ�����㣬��������û�������ʾͲ����ˡ�";

	if (arrayp(obs = me->query_temp("hire")))
	{
		obs -= ({ 0 });
		fam = query("family/family_name");
		obs = filter_array(obs, (: $1->query("family/family_name") == $(fam) :));
		if (sizeof(obs))
			return obs[0]->name() + "���ڲ�����������һ��ô������������";
	}

	if (me->query("combat_exp") < ob->query("combat_exp") * 2 / 3)
		return "���˰ɣ�" + ob->name() + "�书Ҳǿ��̫�࣬����û��Ȥ���㡣";

	if (ob->query("combat_exp") * 2 < me->query("combat_exp"))
		return "Ŷ�����书��ô�ã�" + ob->name() + "���°ﲻ����ʲôæ�ɡ�";

	cost = info[ob->query("npc_level") - 1]["cost"];
	message_vision("$N΢΢һЦ���������ðɣ�������Ҳ����˼��˼�����������͵�����Ҳ��С�ġ���\n"
		       "$N��ϸ������һ�������$n�����������ɣ���" + chinese_number(cost) + "���ƽ�ɡ� ��\n",
		       this_object(), me);
	me->set_temp("pending/rent/cost", cost);
	me->set_temp("pending/rent/helper", ob);
	return 1;
}

void create_all_helper()
{
	object *obs;
	int *lvls = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
	int lvl;
	object ob;
	string startroom;

	if (! stringp(startroom = query("startroom")) ||
	    environment() != find_object(startroom))
		return;

	obs = query_temp("helpers");
	if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });
	lvls -= obs->query("npc_level");
	while (sizeof(obs) < 15)
	{
		lvl = lvls[random(sizeof(lvls))];
		ob = new(CLASS_D("generate") + "/helper");
		// initialize the npc
		ob->set("npc_level", lvl);
		ob->set_temp("renter", this_object());
		NPC_D->init_npc_skill(ob, lvl);
		ob->init_man(info[lvl - 1]);
		lvls -= ({ lvl });
		obs += ({ ob });
		ob->create_family("���͵�", 0, "����");
	}

	obs = sort_array(obs, (: (int) $1->query("npc_level") - (int) $2->query("npc_level") :));
	set_temp("helpers", obs);
}

void remove()
{
	object *obs;
	object ob;

	obs = query_temp("helpers");
	if (! arrayp(obs)) return;
	obs -= ({ 0 });

	// �������е�ʦ�ֵ�
	foreach (ob in obs) ob->destruct_by_owner();
}

void move_or_destruct()
{
	remove();
}

void reset()
{
	create_all_helper();
}
