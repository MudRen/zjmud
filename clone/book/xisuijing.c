// xisuijing.c ϴ�辭

inherit ITEM;

#include <ansi.h>

int do_study(string);

string* skill = ({
	"whip",
	"finger",
	"hand",
	"cuff",
	"claw",
	"strike",
});

void create()
{
	set_name(YEL "ϴ�辭" NOR, ({ "xisui jing" }));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long","�Ȿ��ֽͲ�������������ѧ�伮���Ǵ�Ħ������ھ������׽һ��"ZJURL("cmds:canwu1 xisui jing")+ZJSIZE(20)+"����"NOR"�����ľ����伮��\n");
		set("value", 10);
		set("no_sell", 1);
		set("no_get", 1);
		set("no_put", 1);
		set("material", "paper");
	}
}

void init()
{
	add_action("do_study","canwu1");
}

int do_study(string arg)
{
	object where;
	object ob = this_object();
	object me = this_player();
	int cost, exp;
	int i;

	where = environment(me);
	if (! arg || ! id(arg))
		return notify_fail("��Ҫ����ʲô��\n");

	if ((string)where->query("short") != "��ĦԺ��¥")
		return notify_fail("ϴ�辭ֻ���ڴ�ĦԺ�����\n");

	if (me->query_skill("literate", 1) < 100)
	{
		write("���ֽͲ������ȥ������ʲô����������\n");
		return 1;
	}

	if (me->is_busy()) {
	      call_out("do_lian3", 5, me);
		return notify_fail("��������æ���ء�\n");
            }

	if (me->is_fighting())
		return notify_fail("���޷���ս����ר�������ж���֪��\n");

	if (me->query_temp("auto"))
		return notify_fail("�㲻���Ѿ��ڹһ�����\n");

	exp = (int)me->query("combat_exp");
	if (exp < 300000)
	{
		write("���ʵս���鲻�㣬���ܲ���ϴ�辭��\n");
		return 1;
	}

	me->add("neili", -10 - random(10));

	cost = 50 + random(50);
	if (me->query("jing") > cost)
	{
		for (i = sizeof(skill); i > 0; i--)
		{
			if (me->query_skill(skill[i-1], 1) < 180 &&
			    me->query_skill(skill[i-1], 1) >= 100 &&
			    me->can_improve_skill(skill[i-1]))
			{
				me->improve_skill(skill[i-1], 5 + random(30));
			}
		}
		write(sprintf("�����ϴ�辭�ϵľ��ģ��ƺ��е��ĵá�\n"));
		me->receive_damage("jing", cost);
                tell_object(me,ZJFORCECMD("canwu1 xisui jing"));
	} else
	{
		me->set("jing", 0);
		me->set_temp("auto", 1);
		write("�����ڹ���ƣ�룬�޷�ר����������ϴ�辭��\n");
	    if (me->query("neili") >500) {
	        call_out("do_lian3", 2, me);
            } else
           {
		write("����������㣬�ȴ��ָ���...\n");
              tell_object(me,ZJFORCECMD("use huxin dan"));
	        call_out("do_lian3", 10, me);
            }

	}

	return 1;
}


void do_lian3(object me)
{
	if (! objectp(me))
		return;
	   me->delete_temp("auto");
         tell_object(me,ZJFORCECMD("exert regenerate")+ZJFORCECMD("canwu1 xisui jing"));
}