
//������������Ʒ�б�
string *random_ob = ({
    "/clone/money/gold",
    "/clone/money/coin",
    "/clone/money/silver",
});

int clean_up()
{
	return 1;
}

void init()
{	
	set("no_clean_up_fb", 1);
	add_action("do_sousuo", "sousuo");
/*
	set("action_list", ([
		"����":"sousuo",
	]));
*/
	//ʶ�����ط���
	if ( this_object()->query("anniu_hide")) 
		add_action("do_anniu", "anniu");
	if ( this_object()->query("jiguan")) 
		add_action("do_anniu", "anniu");
	
}
int do_sousuo(object me)
{
	object ob;
	object oba, obb, obc, obd;
	string id = random_ob[random(sizeof(random_ob))];//�����Ʒ
	me = this_player();
	
	oba = present("tu fei", environment(me));
	obb = present("tufei tou", environment(me));
	obc = present("han fei", environment(me));
	obd = present("hanfei tou", environment(me));
	
	if (oba) {
		oba->kill_ob(me);
		me->kill_ob(oba);
		return notify_fail(oba->name()+"�����������ò��ͷ��ˣ����ڴ�ү��ǰ͵������\n");
	}
	if (obb) {
		obb->kill_ob(me);
		me->kill_ob(obb);
		return notify_fail(obb->name()+"�������������������͵�������ҿ�����������\n");
	}
	
	if (obc) {
		obc->kill_ob(me);
		me->kill_ob(obc);
		return notify_fail(obc->name()+"���㡰�ٺ٣���һЦ���㿴��ë���Ȼ��\n");
	}
	if (obd) {
		obd->kill_ob(me);
		me->kill_ob(obd);
		return notify_fail(obd->name()+"���㡰�ٺ٣���һЦ���㿴��ë���Ȼ��\n");
	}
	/*
	if (me->query_temp("sousuo_buy", 1) > time()) 
		return notify_fail(sprintf("����æ�����������ż���\n"));
	*/
	if (query_temp("sousuo")) 
		return notify_fail(sprintf("�����Ѿ����㷭�õ׳����ˣ������ط��ɣ�\n"));
	
	//��ԵԽ�߼���Խ��
	if (random(200) < me->query("kar")) {
		ob = new(id);
		ob->move(me);
		tell_object(me, sprintf("��ϲ���Ȼ�ҵ���%s��\n", ob->name()));
	} else
		tell_object(me, sprintf("���������Ƶ����������﷭�������ʲôҲû�ҵ���\n"));
	
	//me->set_temp("sousuo_buy", time() + random(3) + 2);
	add_temp("sousuo", 1);
	return 1;
}
