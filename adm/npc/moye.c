// moye.c  Īа
// Written by Doing Lu  1998/11/2

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

int	ask_me();
int	no_money();

#define ITEM_TYPE       0
#define ITEM_STYPE      1
#define ITEM_UNIT       2
#define ITEM_WEIGHT     3
#define ITEM_POINT      4
#define ITEM_PROP       5

static mapping item_type = ([
//      ����	�������  �̳��ļ�  ��λ  ���� ���� �������
	"��"   : ({ "weapon", "blade",  "��", 150, 100, 0, }),
	"��"   : ({ "weapon", "sword",  "��", 150, 100, 0, }),
	"��"   : ({ "weapon", "club",   "��", 150, 100, 0, }),
	"��"   : ({ "weapon", "staff",  "��", 150, 100, 0, }),
	"��"   : ({ "weapon", "hammer", "��", 350, 100, 0, }),
	"��"   : ({ "weapon", "axe",    "��", 220, 100, 0, }),
	"��"   : ({ "weapon", "whip",   "��", 150, 100, 0, }),
	"�̱�" : ({ "weapon", "dagger", "֧", 30,  100, 0, }),
	"����" : ({ "armor",  "armor",  "��", 150, 80,
		     ([ "armor_prop" : ([ "parry"   : "apply_armor() / 15 + 1",
					  "armor"   : "apply_armor()",
				       ]),
		      ]) }),
	"ս��" : ({ "armor",  "cloth",  "��", 200, 100, 0, }),
	"ѥ��" : ({ "armor",  "boots",  "˫", 60,  40,
		     ([ "armor_prop" : ([ "dodge"   : "apply_armor() / 10 + 1",
					  "armor"   : "apply_armor()",
				       ]),
		      ]) }),
	"ͷ��" : ({ "armor",  "head",   "��", 75,  50,  0, }),
	"����" : ({ "armor",  "pants",  "��", 100,  50,  0, }),
	"����" : ({ "armor",  "waist",  "��", 80,  40,  0, }),
	"����" : ({ "armor",  "wrists", "��", 50,  25,
		     ([ "armor_prop" : ([ "sword"   : "apply_armor() / 6 + 1",
					  "staff"   : "apply_armor() / 6 + 1",
					  "blade"   : "apply_armor() / 6 + 1",
					  "club"    : "apply_armor() / 6 + 1",
					  "hammer"  : "apply_armor() / 6 + 1",
					  "whip"    : "apply_armor() / 6 + 1",
					  "dagger"  : "apply_armor() / 6 + 1",
					  "stick"   : "apply_armor() / 6 + 1",
					  "unarmed" : "apply_armor() / 6 + 1",
					  "claw"    : "apply_armor() / 6 + 1",
					  "cuff"    : "apply_armor() / 6 + 1",
					  "hand"    : "apply_armor() / 6 + 1",
					  "strike"  : "apply_armor() / 6 + 1",
					  "finger"  : "apply_armor() / 6 + 1",
					  "parry"   : "apply_armor() / 6 + 1",
					  "whip"    : "apply_armor() / 6 + 1",
					  "armor"   : "apply_armor()",
				       ]),
		      ]) }),
	"��"   : ({ "weapon", "xsword", "֧", 30,  100, 0, }),
	"����" : ({ "armor",  "hands",  "˫", 45,  100,
		    ([ "armor_prop" : ([ "hand"   : "10",
					 "strike" : "10",
					 "unarmed_damage" : "apply_damage()",
					 "armor"  : "10",
				       ]),
		     ]) }),
	"ָ��" : ({ "armor",  "hands",  "��", 35,  100,
		    ([ "armor_prop" : ([ "claw"   : "10",
					 "finger" : "10",
					 "unarmed_damage" : "apply_damage()",
					 "armor"  : "10",
				       ]),
		     ]) }),
]);

void create()
{
	set_name("Īа", ({ "mo ye", "moye", "mo" }));
	set("long", "����������������һ����ʳ�˼��̻��ģ����������������ʦ�ɽ������ӡ�\n" );

	set("nickname", HIY "����" NOR);
	set("gender", "Ů��");
	set("attitude", "friendly");

	set("age", 1525);
	set("shen_type", 0);
	
	set("str", 1000);			// ��֤������Ϊ���ɹ�������ܲ��˶���
       set("icon","05005");
	set("inquiry", ([
		
		"����" : (: ask_me :),
		"Ǯ����":(: no_money :),
	
		"�˻�" : "����ͰѶ������ɽ�������������",
		"ԭ��" : "���Ƶ��߿ɲ���û��ԭ�ϰ���Ҫ�����ƺ������͵���"
			 "����ʯһ��Ķ�����\n	  Ҫ�����ƺ÷��߾�"
			 "�������˿��Щ��������Щԭ�Ϻ����ң����������󰡣�\n",
		"�۸�" : "���ԭ�ϸ��ҿ���(show)���Ҿ��ܹ�����һ����Ǯ��",
	]));

	setup();

	set("startroom", "/d/item/xiaowu");
	check_clone();
	if (! this_object()) return;

	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object me;

	// ���ѯ�ʱ�־
	if (! objectp(me = this_player()) || ! interactive(me))
		return;

	add_action("do_show", "show");
	add_action("do_answer", "answer");
	if (me->query_temp("item/status") == "item_gived")
	{
		remove_call_out("greeting2");
		call_out("greeting2", 1, me);
	} else
	{
		remove_call_out("greeting");
		call_out("greeting", 1, me);
	}
}

void greeting(object me)
{
	if (objectp(me) && environment(me) == environment())
	{
		message_vision("$NЦ�Ŷ�$n˵����ã�������������"
			       "��\n", this_object(), me);
	}
}

void greeting2(object me)
{
	if (objectp(me) && environment(me) == environment())
	{
		message_vision("$N��$n˵����Ǯ�Ϳ��Դ�����Ŷ��\n",
			       this_object(), me);
	}
}

int do_show(string arg)
{
	object	me;
	object	ob;
	string	msg;
	string  mat;
	int	power_point;
	int	value;
	int	n;

	me = this_player();
	if (! arg)
		return notify_fail("�����ʲô����Ҫ������ô��\n");

	mat = arg;
	power_point = 0;

	if (! objectp(ob = present(mat, me)))
		return notify_fail("���˰ɣ�������û�� " + mat + " ���ֶ�����\n");

	if (! ob->query("material_attrib"))
	{
		message_vision("$Nһ㶣���$n˵�������ֶ���Ҳ��������"
			       "�ƣ���û��˵����\n", this_object(), me);
	}

	power_point = ob->query("power_point");
	if (! power_point)
	{
		message_vision("$N��ϸ�Ŀ��˿�$n�ó���ԭ�ϣ�̾����"
			       "����ԭ�Ͽ����Ѿ��Ƕ��첻���ˡ�\n",
			       this_object(), me);
		return 1;
	}
	value = power_point * 2 + 10;
	msg = sprintf("$N��ϸ���˿�$n�ó���ԭ�ϣ�˵��������ԭ�ϴ�����ߣ�ֻ��Ҫ%s���ƽ���ô�������Ǽ۸�ܺ���ɣ�\n" +
                      "Ҫ��û���⣬�����ԭ�ϲ���Ǯ��\n" +
                      "��˳��������һ�䣺�ڴ�������У�����Ҫ��æ���װ��Ʒ�ʣ���ĵ�ǰ����������������ܵ���200�㡣\n", chinese_number(value));
	message_vision(msg, this_object(), me);

	return 1;
}

// ������ʾ��Ϣ
int ask_me()
{
	message_vision("$N��$n˵����" 
		"����Ҫ�����Լ��ĵ�����\n"
		"�����������Ϊ�����������������������������ޡ��Ⱥͻ��ף����ǵ�һ���ġ�\n"
		"���Ȱ�ԭ�ϸ��ҿ��������ȹ���һ�¼�Ǯ��������������Ǿ�һ�ֽ�Ǯ��һ�ֽ�����\n", this_object(), this_player());
	return 1;
}

int no_money()
{
	object me;
	object ob;

	me = this_player();
	if (me->query_temp("item/status") == "item_gived")
	{
		message_vision("$N������һ��$n����ûǮ�Ǿ��´ΰɣ�\n",
			       this_object(), me);
		if (objectp(ob = query_temp("item/accept")))
		{
			message_vision("$N��" + ob->name() + "������$n��\n", this_object(), me);
			if (! ob->move(me))
				ob->move(environment());
		}
		delete_temp("item");
		me->delete_temp("item");
		return 1;
	}

	message_vision("$N�۾�һ�ɣ���$n˵����ûǮ����ûǮ����ɶ�£�"
		       "���ֲ��ǲ���ү��\n", this_object(), me);
	return 1;
}

// ���ܶ���
int accept_object(object me, object ob)
{
	string status,str;
	int    i,val;

	status = query_temp("item/status");
	if (status == "look_working")
	{
		message_vision("$N���ŵĶ�$n˵���𳳣��ɽ����ڸɻ��ء�\n",
			       this_object(), me);
		return 0;
	}

	if (status == "waiting")
	{
		if (query_temp("item/player_id") == me->query("id"))
		{
			command("say ��úú͸ɽ�̸���ٴ��");
			return 0;
		}

		message_vision("$N��$n˵���𳳣��ɽ����ں͹˿�̸���ء�\n",
			       this_object(), me);
		return 0;
	}

	if (status == "accept")
	{
		if (query_temp("item/player_id") != me->query("id"))
		{
			command("say �����ںͱ�Ŀ��������أ����ȱ����ң�");
			return 0;
		}

		if (! ob->query("money_id"))
		{
			command("say �㻹�ǿ�㽻Ǯ�ɣ�Ҫ��ûǮ����˵��");
			return 0;
		}
	}

	if (ob->query("material_attrib") &&
	    ob->query("power_point"))
	{
		// �����ֵ
		val = ob->query("power_point") * 2 + 10;
		message_vision("$N��$n˵�����ܺã������ԭ�ϴ��������Ҫ" +
			       chinese_number(val) + "���ƽ𣬽�Ǯ�ɡ�\n",
			       this_object(), me);
		val *= 10000;
		if (wizardp(me))
		{
			message_vision("$N��ϸ���˿�$n��Ц��˵����ԭ"
				       "������ʦ����ô����������ˡ�\n",
				       this_object(), me);
			val = 1;
		}
		ob->set("item/value", val);
		me->set_temp("item/status", "item_gived");
		me->set_temp("item/value", val);
		set_temp("item/status", "accept");
		set_temp("item/player_id", me->query("id"));
		set_temp("item/accept", ob);

		// �����һ��ʱ��û�н�������ߴ���
		remove_call_out("time_out");
		call_out("time_out", 30, me, ob);
		return 1;
	}

	if (ob->query("money_id"))
	{
		object origin;
		mixed p;
		string *types;

		if (me->query_temp("item/status") == "answer_type")
		{
			message_vision("$Nҡҡͷ����$n˵����˵��Ҫ��ʲô������\n",
				       this_object(), me);
			return 0;
		}

		if (me->query_temp("item/status") != "item_gived")
		{
			message_vision("$N��$n�ݹ�ȥ��" + ob->name() +
				       "���˻����������޹�����»��\n",
				       this_object(), me);
			return 0;
		}

		if (ob->value() < me->query_temp("item/value"))
		{
 			message_vision("$N��$n˵���Բ��𣬱��꿪��һ"
				       "ǧ����������û�д���ۿۡ�\n",
				       this_object(), me);
			return 0;
		}

		origin = query_temp("item/accept");
		if ((p = origin->query("can_make")) == "all")
		{
			types = keys(item_type);
		} else
		if (arrayp(p))
			types = p;
		else
		if (stringp(p))
			types = ({ p });

		p = origin->query("not_make");
		if (arrayp(p))
			types -= p;
		else
		if (stringp(p))
			types -= ({ p });

		set_temp("item/types", types);
		set_temp("item/money", ob);
		ob->move(this_object());

		str = ZJOBLONG"Īа����˵���ã���͸���������������ʲô����������������ͣ�\n"ZJOBACTS2+ZJMENUF(4,4,9,30);
		for(i=0;i<sizeof(types);i++)
		{
			str += types[i]+":answer "+types[i]+ZJSEP;
		}
		write(str+"\n");

		me->set_temp("item/status", "answer_type");
		return -1;
	}

	message_vision("Īа�۾�һ�ɣ���$N˵�����������Щ������ʲô���Ҳ�Ҫ��\n", me);
	return 0;
}

int do_answer(string arg)
{
	object money;
	object ob;
	object me;
	object ganjiang;

	me = this_player();
	if (me->query_temp("item/status") != "answer_type")
		return 0;

	if (! arg)
		return notify_fail("��Ҫ�ش�ʲô��\n");

	message_vision("$n��$N�����ʹ���" + arg + "�ɣ�\n",
		       this_object(), me);

	if (member_array(arg, query_temp("item/types")) == -1 ||
	    undefinedp(item_type[arg]))
	{
		message_vision("$N�����һ�´��˸����磬һ���޹��Ŀ���$n��\n",
			       this_object(), me);
		return 1;
	}

	// ����ɽ�����
	if (! objectp(ganjiang = present("gan jiang",environment(this_object()))))
	{
		message_vision("$N���˿����ܣ�����һ����˵�����ɽ���"
			       "�������ڣ�û�취����...����������ɡ�\n",
			       this_object());
		if (ob = query_temp("item/accept"))
		{
			message_vision("$N��" + ob->name() + "������$n��\n",
				       this_object(), me);
			if (! ob->move(me))
				ob->move(environment());
		}
		delete_temp("item");
		me->delete_temp("item");
		return 0;
	}

	if (objectp(money = query_temp("item/money")))
		destruct(money);
	delete_temp("item/money");
	set_temp("item/status", "look_working");
	me->set_temp("item/status", "waiting");
	ob = query_temp("item/accept");
	ob->set("item/ctype", arg);
	ob->set("item/type", item_type[arg][ITEM_TYPE]);
	ob->set("item/stype", item_type[arg][ITEM_STYPE]);
	ob->set("item/unit", item_type[arg][ITEM_UNIT]);
	ob->set("item/point", ob->query("power_point") * item_type[arg][ITEM_POINT] / 100);
	ob->set("item/owner", me);
	ob->set("item/owner_id", me->query("id"));
	ob->set("item/owner_name", me->name(1));
	ob->set("item/wscale", item_type[arg][ITEM_WEIGHT]);
	ob->set("item/prop", item_type[arg][ITEM_PROP]);
	message_vision("$N��" + ob->name() + "������$n��\n",
		       this_object(), ganjiang);
	if (! ob->move(ganjiang))
		error("Can move the object to ganjiang.");
	remove_call_out("time_out");
	ganjiang->accept_object(this_object(), ob);
	return 1;
}

void time_out(object me, object ob)
{
	object money;
	int at_present;

	money = query_temp("item/money");

	if (! objectp(me))
		me = find_player(query_temp("item/player_id"));

	if (! objectp(me) || environment(me) != environment())
	{
		command("say ��֣��ղ���λ�����أ���ô������ˣ�\n");
		at_present = 0;
	} else
	{
		command("say ��������ԥ�ɣ��ҿɲ��ܸ�����ţ���������ɣ�");
		at_present = 1;
	}

	delete_temp("item");
	if (objectp(me))
		me->delete_temp("item");

	if (money)
	{
		if (at_present)
			command("give " + money->query("id") +
				" to " + me->query("id"));

		if (environment(money) == this_object())
			command("drop " + money->query("id"));
	}

	if (ob)
	{
		if (at_present)
			command("give " + ob->query("id") +
				" to " + me->query("id"));

		if (environment(ob) == this_object())
			command("drop " + ob->query("id"));
	}
}
