//baoxiang.c

#include <ansi.h>
inherit ITEM;
//�س���Ʒ����б�
string *random_ob = ({
    "/clone/money/gold",
});
//�������
string *random_item = ({
    "/clone/shizhe/jinsha",
});

void create()
{
	set_name(CYN"����" NOR, ({ "bao xiang" }));
	set("long", "һ�ڴ����ӣ�����"+ZJURL("cmds:open_2 bao xiang")+ZJSIZE(22)+"��"NOR+"��������\n");
	set("unit", "��");
	set("value", 10);
	set("no_get", "���ӷ·����˸�һ������ʹ�����̵�����Ҳ�᲻����");

	set_weight(1000000);
	
	setup();
}
void init()
{
	add_action("do_open_2", "open_2");
}
int do_open_2(string arg)
{
	string id2 = random_ob[random(sizeof(random_ob))];//�س���Ʒ�б�
	string id = random_item[random(sizeof(random_item))];//�������Ʒ�б�
	object ob, obj;
	object me = this_player();
	object player;
	int i,num;
	object oba, obb, obc, obd;
	int ok = 0;
	object *obs = all_inventory(environment(this_object()));
	
	if (!arg || arg != "bao xiang")
		return notify_fail("�����ʲô����\n");
	
	oba = present("tu fei", environment(me));
	obb = present("tufei tou", environment(me));
	obc = present("han fei", environment(me));
	obd = present("hanfei tou", environment(me));
	
	foreach(player in obs) {
		if (userp(player))
		{
			if (oba) {
				oba->kill_ob(player);
				player->kill_ob(oba);
				tell_object(player, oba->name()+"�����������ò��ͷ��ˣ����ڴ�ү��ǰ͵������\n");
				ok = 1;
			}
			if (obb) {
				obb->kill_ob(player);
				player->kill_ob(obb);
				tell_object(player, obb->name()+"�������������������͵�������ҿ�����������\n");
				ok = 1;
			}
			if (obc) {
				obc->kill_ob(player);
				player->kill_ob(obc);
				tell_object(player, obc->name()+"���㡰�ٺ٣���һЦ���㿴��ë���Ȼ��\n");
				ok = 1;
			}
			if (obd) {
				obd->kill_ob(player);
				player->kill_ob(obd);
				tell_object(player, obd->name()+"���㡰�ٺ٣���һЦ���㿴��ë���Ȼ��\n");
				ok = 1;
			}
		}
	}
	if (ok > 0)
		return 1;
	message_vision( "$N����" + name() + "��"NOR"\n", me);
	
	if (!query("open_2")) {
		switch (random(4))
		{
			case 0 : 
			case 1 :
			case 2 :
				ob = new(id);
			break;
		}
		if (ob && ob->move(me))
			tell_object(me, "��ϲ������"+ob->name()+"��\n");
		
		//id2=�ƽ� id=��ɰ
		obj = new(id2);
            num=10+random(50);
            obj->set_amount(num);
		if (obj->move(me))
                tell_object(me, "��ϲ������"+chinese_number(num) + obj->query("unit")+ obj->name()+"��\n");
                //tell_object(me, "��ϲ������"+chinese_number(obj->query_amount() ? obj->query_amount() : 1 ) + obj->query("unit")+ obj->name()+"��\n");

		set("open_2", 1);
	} else 
		tell_object(me, "���������Ķ����Ѿ������ù��ˡ�\n");
	
	return 1;
}
