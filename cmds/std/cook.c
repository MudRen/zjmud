// cook.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string  skill;
	string *menu_list;
	mapping menu;
	string  msg;
	object  cailiao;
	object  ob;

	skill = me->query_skill_mapped("cooking");
	if (! skill)
		return notify_fail("���ȼ�����Ҫʹ�õĲ��ա�\n");

	menu = SKILL_D(skill)->query_menu(me);
	if (! arg)
	{
		if (! menu || sizeof(menu) < 1)
		{
			write("�㲻������" + to_chinese(skill) +
			"���κβ��ȡ�\n");
			return 1;
		}

		msg = "������ʹ��" + to_chinese(skill) + "����" +
		      implode(keys(menu), "��") + "��Щ���ȡ�";
		write(msg+"\n");
		return 1;
	}

	if (! objectp(cailiao = present("cai liao", me)) ||
	    cailiao->query_amount() < 1)
	{
		write("��������ͷû�в��ϣ�û�����ˡ�\n");
		return 1;
	}

	menu_list = 0;
	if (undefinedp(menu[arg]) &&
	    ! sizeof(menu_list = filter_array(keys(menu),
					(: member_array($(arg), $(menu)[$1]) != -1 :))))
	{
		write("�����ڻ���֪����ô����" HIG + arg + NOR
		      "����ζ�ˡ�\n");
		return 1;
	}
	if (menu_list) arg = menu_list[0];

	if ((int)me->query_skill(skill, 1) < 50)
	{
		write("�����" + to_chinese(skill) + "���ǲ�Ҫ�˷Ѳ����ˡ�\n");
		return 1;
	}

	message_vision("$N�������ӣ����ù���ư�衢���Ͳ�"
		       "�ף����ĵ��Ƴ�һ��" + arg + "����\n", me);
	cailiao->add_amount(-1);
	ob = new("/clone/food/dish");
	ob->set_name(arg, menu[arg] + ({ "dish" }));
	ob->set("long", "һ����" + me->name(1) + "�������Ƶ�" +
			ob->name() + "��\n");
	ob->set("skill", skill);
	ob->set("level", (int)me->query_skill(skill, 1));
	ob->set("by", me->query("id"));
	ob->move(me, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : cook [<��������>]

HELP );
	return 1;
}
