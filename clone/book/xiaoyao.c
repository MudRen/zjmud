// xiaoyao.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
	set_name(HIY "������ľ�" NOR, ({ "ziwu jing", "jing" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���������õ��鼮��������С��"
			    "д�š�������ľ��������֡�\n");
		set("material", "paper");
		set("skill", ([
			"name"      : "xiaoyao-qixue",
			"jing_cost" : 50,
			"difficulty": 45,
			"max_skill" : 160,
			"min_skill" : 30,
		]));

		set("can_make", ([
			"jingqi"   : 50,	// ������
			"dahuan"   : 80,	// �󻹵�
			"jiedu"    : 100,       // ţ�ƽⶾ��
			"heishi"   : 180,       // �񶴺�ʯ��
			"xiongshe" : 250,       // ��ת������
		]));
	}
	setup();
}

