// taohua.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
	set_name(HIG "�һ�ҩ��" NOR, ({ "taohua yaoshu", "yaoshu" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����Ƶ��鼮�������ù�׭��"
			    "д�š��һ�ҩ���������֡�\n",

		);
		set("material", "paper");
		set("skill", ([
			"name": "taohua-yaoli",
			"jing_cost": 60,
			"difficulty": 40,
			"max_skill": 160,
			"min_skill": 30,
		]));

		set("can_make", ([
			"liuhe" : 80,	   // ���Ϸ���ɢ
			"qingxin" : 100,	// ���Ķ���ɢ
			"zhending": 150,	// ��Ԫ��ɢ
			"dieda" : 80,	   // ����������
			"huojin" : 100,	 // �����Ѫ��
			"tongmai" : 150,	// ����ͨ����
			"jiedu" : 100,	  // ţ�ƽⶾ��
			"jiuhua" : 200,	 // �Ż���¶��
			"wuchang" : 250,	// �޳���
		]));
	}
	setup();
}
