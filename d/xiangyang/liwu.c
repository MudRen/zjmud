// Room: /d/xiangyang/liwu.c  é������
// Date: Feb . 3 2002 by Pound

#include "room.h"

inherit ROOM;
// ���ҵ��ӿ���ͨ�������������ҩ�������ֲ(zhonghua)��ҩ����ҩ(zhao)���Լ�����(make)
// �˴���Ϊҩ������ͬ�ȼ���ҽҩ֪ʶ�����ֱܷ����ҩ�ﲻͬ���ȼ�Խ���ֱܷ��ҩ��Խ�ࡣ
// ����ҩ�����ڲ��Ͷ�������ÿ��ˢ�º�ȫ�����ҵ���ֻ���ҵ�����ҩ�
string* med1 = ({"jingqi", "dieda", "liuhe", });
string* med2 = ({"jingqi", "dieda", "liuhe", "huojin", "qingxin", });
string* med3 = ({"jingqi", "dieda", "liuhe", "huojin", "qingxin", "jiedu", "tianxin", });
string* med4 = ({"jingqi", "dieda", "liuhe", "huojin", "qingxin", "jiedu", "tianxin", "zhending", "tongmai", });
string* med5 = ({"jingqi", "dieda", "liuhe", "huojin", "qingxin", "jiedu", "tianxin", "zhending", "tongmai", "shengsheng", "shengsheng", });

void create()
{
	set("short", "����");
	set("long", @LONG
������һ���ܷ��С�ݣ�����ȥ�����ղ������Ʒ�ĵط�������ǽ��
�ڷ���һ��ľ������ϸ��ȥ�������Ȼ�кܶ�ҩ�ĺ�����С��ƿ�����Ƕ�
û������ǩ������Ҫ�нϸ����ҽҩ֪ʶ�ſ��ֱܷ��������ҩ�����ҳ�
���õĵ�ҩ��zhao yao����
LONG);
	set("searched", 0);
	set("exits", ([
	    "south"  : __DIR__"maoshe",
	]));
	create_door("south", "ľ��", "north", DOOR_CLOSED);
	setup();
}


void init()
{
	add_action("do_search", "zhao");
}


int do_search(string arg)
{
	object ob, me;
	int lvl;
	me = this_player();
	lvl = me->query_skill("yaowang-miaoshu", 1);

	if (! arg || arg == "") 
	    return 0;

	if (me->is_fighting())
		return notify_fail("��ܵ�ʱ���㻹���й�����ҩ��\n");
	if (me->is_busy())
		return notify_fail("�����Ȱ���ͷ������æ��ɡ�\n");

	if (me->query("jing") < 300)
		return notify_fail("�����ھ������Լ��У��޷���ҩ��\n");
	if (lvl < 100 || me->query_skill("medical", 1) < 100)
	    return notify_fail("�㿴����ȥ��ʼ���޷��ֱ����ҩ���������ҪŬ������ҽҩ֪ʶ��\n");
    
	if (arg == "yao" || arg == "medicine" || arg == "muchu" || arg == "cabinet")
	{
	    if (query("searched") > 2)
		return notify_fail("�����ղŵ�һ���ң��Ѿ����ѷֱ��������ҩ���ˡ�\n");
	    if (lvl > 150 && lvl <= 180)
		ob = new("/clone/medicine/" + med2[random(sizeof(med2))]);
	    else if (lvl > 180 && lvl <= 210)
		ob = new("/clone/medicine/" + med3[random(sizeof(med3))]);
	    else if (lvl > 210 && lvl <= 240)
		ob = new("/clone/medicine/" + med4[random(sizeof(med4))]);
	    else if (lvl > 240)
		ob = new("/clone/medicine/" + med5[random(sizeof(med5))]);
	    else
		ob = new("/clone/medicine/" + med1[random(sizeof(med1))]);

	    add("searched", 1);     
	    message_vision("$N��һ��Сƿ�����ҵ�һ��" + ob->query("name") + "��\n", me);
	    ob->move(me);
	    me->add("jing", -100);
	    me->start_busy(2 + random(3));
//����æʱ��ʹÿ��ˢ�³���ҩ�ﲻ����ֻ��һ�����ٿ�ĵ���ȫ���õ���ÿλ�ڳ����Ӷ����������ջ�űȽϺ���
	    return 1;
	}
}   

