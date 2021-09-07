// yaowang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
	set_name(HIM "ҩ����ƪ" NOR, ({ "yaowang shenpian", "shu" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��������С���ӣ����湤������"
			    "д�š�ҩ����ƪ�������֡�\n",

		);
		set("material", "paper");
		set("skill", ([
			"name": "yaowang-miaoshu",
			"jing_cost": 60,
			"difficulty": 40,
			"max_skill": 200,
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
			"tianxin" : 100,	// ���Ľⶾ��
			"shengsheng" : 200,     // �����컯��
		]));
	}
	setup();
}
