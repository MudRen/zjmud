// friend.c
// by luoyun 2016.11.10
// ����ϵͳ
#include <localtime.h>

int do_list(object me, string arg);
int do_del(object me, string arg);
int do_add(object me, string arg);
int do_sms(object me, string arg);
int do_jilu(object me, string arg);
int do_apply(object me, string arg);
int do_yesno(object me, string arg);

nosave int limit = 15;

int main(object me, string arg)
{
	string line="", msg, type, id;

	
	if (!wizardp(me) && me->query("id") != "luoyun") {
		tell_object(me, "�˹������ڱ�д�У�����ʱ�����������Ź��档\n");
		return 1;
	}
	
	if (!arg) {
		msg = ZJOBLONG+"��ѡ��\n";
		msg += ZJOBACTS2+ZJMENUF(3,3,9,30);
		msg += "������Ϣ:friends -apply";
		msg += ZJSEP"����������Ϣ:friends -jilu -all";
		msg += ZJSEP"�����б�:friends -list";
		write(msg +"\n");
	} else {
		if ( sscanf(arg, "%s %s", type, arg) == 2);
		else { 
			type = arg; 
			arg = "";
		}
				
		switch(type) {
			case "-list_a" :
				id = arg;
				msg = ZJOBLONG+"��ѡ��\n";
				msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
				msg += "������Ϣ:friends -jilu -wd " + id;
				msg += ZJSEP"������Ϣ:friends -sms " + id;
				msg += ZJSEP"��ռ�¼:friends -jilu -clear "+id;
				msg += ZJSEP"��ʷ��¼:friends -jilu " + id;
				msg += ZJSEP"ɾ������:friends -del " + id;
				write(msg +"\n");
			break;
			case "-list" :
				do_list(me, arg);
			break;
			case "-del" :
				do_del(me, arg);
			break;
			case "-add" :
				do_add(me, arg);
			break;
			case "-sms" :
				do_sms(me, arg);
			break;
			case "-jilu" :
				do_jilu(me, arg);
			break;
			case "-apply" :
				do_apply(me, arg);
			break;
			case "-yesno" :
				do_yesno(me, arg);
			break;
		}
	}
	
	return 1;
}

int do_list(object me, string arg)
{
	string line="", *list, msg,str;
	mapping friends;
	int i;
	
	if (friends = me->query("friends")) {
		if (sizeof(friends) < 1) {
			tell_object(me, "�㻹û�к��ѣ��Ͻ����һ���ɡ�\n");
			return 1;
		}
		list = keys(friends);
		list = sort_array(list, (: strcmp :));
		
		for(i=0;i<sizeof(list);i++) {
			if (find_player(list[i]))
				str = HIG+friends[list[i]][0]+NOR;
			else
				str = NOR+WHT+friends[list[i]][0]+NOR;
			line += sprintf("%s:%s", str, "friends -list_a "+list[i]);
			if (i < sizeof(list)-1)
				line += ZJSEP;
		}
		msg = ZJOBLONG+"�����б�\n";
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += line;
		write(msg +"\n");
		return 1;
	} else tell_object(me, "�㻹û�к��ѣ��Ͻ����һ���ɡ�\n");
	return 1;
}

int do_del(object me, string arg)
{
	string msg,id,type;
	
	if ( sscanf(arg, "%s %s", type, id) == 2) {
		if (type == "-yes") {
			if (me->query("friends/"+id)) {
				tell_object(me, "ɾ������"+(me->query("friends/"+id)[0])+"�ɹ���\n");
				me->delete("friends/"+id);
			} else
				tell_object(me, "�Է�������ĺ����б�֮�ڡ�\n");
		}
	} else {
		id = arg;
		if (me->query("friends/"+id)) {
			msg = ZJOBLONG+HIR"�����ڽ���ɾ�����ѡ�"HIY+(me->query("friends/"+id)[0])+HIR"���Ĳ�����"NOR"\n";
			msg += ZJOBACTS2+ZJMENUF(3,3,9,30);
			msg += "ȷ��ɾ��:friends -del -yes " + id;
			msg += ZJSEP"����ɾ��:friends -del -no "+ id;
			write(msg +"\n");
		} else
			tell_object(me, "�Է�������ĺ����б�֮�ڡ�\n");
	}
	
	return 1;
}
int do_yesno(object ob, string arg)
{
	string msg;
	string name, id;
	
	if (sscanf(arg, "%s %s", name, id) == 2) {
		msg = ZJOBLONG+name+"���������Ϊ���ѣ�\n";
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "ͬ��:friends -add -yes "+ id;
		msg += ZJSEP"��ͬ��:friends -add -no "+ id;
		msg += ZJSEP"ȡ��:friends -add -qx "+ id;
		tell_object(ob, msg +"\n");
	}
	return 1;
}

int do_add(object me, string arg)
{
	object ob;
	string type,msg;
	string id;
	int ok;
	
	if (me && arg)
	{		
		if (sscanf(arg, "%s %s", type, id) == 2) {
			if (!ob = find_player(id)) {
				if (!ob = UPDATE_D->global_find_player(id)) {
					tell_object(me, "û������ˡ�\n");
					return 1;
				}
				ok = 1;
			}
			
			if (me->query("friends/"+id) && ob->query("friends/"+me->query(id)) ) {
				me->delete("Friend/temp/"+id);
				ob->delete("Friend/temp/"+me->query("id"));
				tell_object(me, "���"+ob->name()+"�Ѿ��Ǻ����ˡ�\n");
				if (ok == 1)
					destruct(ob);
				return 1;
			}
			if (type == "-yes") {
				if (ob->query("friend/temp/"+me->query("id"), 1)) {
					if (sizeof(me->query("friends")) < limit)
						me->set("friends/"+id, ({ob->name(), time() }) );
					else
						tell_object(me, "��ĺ����Ѿ��ﵽ����"+limit+"�����޷����"+ob->name()+"��\n");	
					
					if (sizeof(ob->query("friends")) < limit) 
						ob->set("friends/"+me->query("id"), ({me->name(), time()}) );
					else
						tell_object(ob, "��ĺ����Ѿ��ﵽ����"+limit+"�����޷����"+me->name()+"��\n");	
					
					ob->delete("friend/temp/"+me->query("id"));
					ob->delete("Friend/temp/"+me->query("id"));
					me->delete("friend/temp/"+id);
					me->delete("Friend/temp/"+id);
					tell_object(me, HIG"��ͬ�����"+ob->name()+"Ϊ���ѡ�"NOR"\n");
					tell_object(ob, HIG+me->name()+"�Ѿ�ͬ�������Ϊ���ѡ�"NOR"\n");
					if (ok == 1) {
						ob->save();
						destruct(ob);
					}
					return 1;
				}
				
				if (!me->query("friend/temp/"+id, 1)) {
					me->set("friend/temp/"+id, ({ob->name(), time()}));
					ob->set("Friend/temp/"+me->query("id"), ({me->name(), time()}));
					tell_object(me, "����"+ob->name()+"��������Ӻ��ѵ�������ȴ���Ӧ��\n");
					ob->force_me("friends -yesno "+me->query("name")+" "+ me->query("id"));
				} else
					tell_object(me, "���Ѿ���"+ob->name()+"��������Ӻ��ѵ����������ĵȴ���\n");
				return 1;
			} else if (type == "-no") {
				ob->delete("friend/temp/"+me->query("id"));
				ob->delete("Friend/temp/"+me->query("id"));
				me->delete("friend/temp/"+id);
				me->delete("Friend/temp/"+id);
				tell_object(ob, me->name()+"�ܾ�������Ӻ��ѵ����롣\n");
				tell_object(me, "��ܾ���"+ob->name()+"��Ӻ��ѵ����롣\n");
				if (ok == 1) {
					ob->save();
					destruct(ob);
				}
			}
		}
		else
		if (sscanf(arg, "%s", id) == 1) {
			if (ob = find_player(id)) {
				if (!userp(ob)) return 1;
				if (!me->query("friends") || (me->query("friends") && !me->query("friends")[ob->query("id")])) {
					msg = ZJOBLONG+"��ȷ���Ƿ����"+ob->name()+"Ϊ���ѣ�\n";
					msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
					msg += "ȷ��:friends -add -yes "+ id;
					msg += ZJSEP"ȡ��:friends -add -qx "+ id;
					write(msg +"\n");
				}
			} else
				tell_object(me, "�����˭Ϊ���ѣ�\n");
		}
	}
	
	return 1;
}

int do_delmsg(object me, string id)
{
	string *line;
	mapping list;
	int i,k;
	
	if (me)
	{
		if (list = me->query("sms/"+id))
		{
			line = keys(list);
			line = sort_array(line, (: strcmp :));
			if (sizeof(line) > 50)
				k = sizeof(line) - 49;
			else
				k = 1;

			for(i=0;i<k;i++) {
				me->delete("sms/"+id + "/" + line[i]);	
			}				
		}
	}
	return 1;
}

int do_sms(object me, string arg)
{
	string msg, id, str;
	object ob;
	int ok=2;
			
	if (sscanf(arg, "%s %s", id, msg) == 2) {
		if (sizeof(msg) > 60 || sizeof(msg) < 1) {
			write(INPUTTXT("�����������"+(me->query("friends/"+id)[0])+"����Ϣ(1-30������)��", "friends -sms "+id+" $txt#")+"\n");
			return 1;
		}
		if (!ob = find_player(id)) {
			if (!ob = UPDATE_D->global_find_player(id)) {
				tell_object(me, "û������ˡ�\n");
				return 1;
			}
			ok = 1;
		}
		if (!ob->query("friends/"+me->query("id"))) {
			tell_object(me, "�㲻�ǶԷ��ĺ��ѣ��޷�������Ϣ��\n");
			return 1;
		}
		
		if (sizeof(me->query("sms/"+id)) >= 50)
			do_delmsg(me, id);
		if (sizeof(ob->query("sms/"+me->query("id"))) >= 50)
			do_delmsg(ob, me->query("id"));
		
		str = HIG+msg+NOR;
		
		me->set("sms/"+id+"/"+time(), ({HIW"���"+HIY+ob->name()+HIW+"˵����"NOR+str, 2}));
		ob->set("sms/"+me->query("id")+"/"+time(), ({HIY+me->name()+NOR"����˵����"+str, ok}));
		tell_object(me, HIW"���"NOR+HIY+ob->name()+NOR+(ok==1?HIR"(����)"NOR:"")+HIW+"˵����"NOR
											+str+" "+ZJURL("cmds:friends -sms "+id)+HIC+ZJSIZE(22)+"����"NOR"\n");
		log_file("friend", sprintf("%s  %s\n", filter_color(me->query("name") +"("+ me->query("id")+")��"+ob->query("name")+"("+id+")˵:"+str), ctime(time())));
		if (ok != 1) {
			tell_object(ob, HIG+me->name()+HIW"����˵����"+str +" "+ZJURL("cmds:friends -sms "+me->query("id"))+HIC+ZJSIZE(22)+"�ظ�"NOR"\n");
		} else {
			ob->save();
			destruct(ob);
		}
	} else {
		id = arg;
			
		write(INPUTTXT("�����������"+HIG+(me->query("friends/"+id)[0])+NOR+"���͵���Ϣ��", "friends -sms "+id+" $txt#")+"\n");
	}
	return 1;
}

int do_jilu(object me, string arg)
{
	string str="",msg,id;
	mapping list;
	string *line;
	int i;
	int GMT;
	mixed *times, time;
	string type, cs;
	int j;
	mapping list_a;
	string *linea;

	if (sscanf(arg, "%s %s", type, id) == 2) {
		if (sizeof(me->query("sms/"+id)) < 1) {
			tell_object(me, "û�������¼��\n");
			return 1;
		}
		if (type == "-wd") {
			if (list = me->query("sms/"+id)) {
				if (sizeof(list) > 0) {
					line = keys(list);
					line = sort_array(line, (: strcmp :));
					
					for(i=0;i<sizeof(line);i++) {
						if (list[line[i]][1] == 1) {
							GMT = to_int(line[i]);
							times = localtime(GMT);
							time = sprintf("%s-%s %s:%s:%s", (times[LT_MON] + 1)+"", times[LT_MDAY]+"", 
													times[LT_HOUR]+"", times[LT_MIN]+"", times[LT_SEC]+"");
						
							str += sprintf("%s(%s)"ZJBR, list[line[i]][0], time);
							me->set("sms/"+id+"/"+line[i], ({list[line[i]][0], 2}));
						}
					}	
					if (str !="") {
						msg = ZJOBLONG+(me->query("friends/"+id)[0])+"��������Ϣ�б�("+(sizeof(line))+"��)��"+ZJBR;
						msg += str;
					} else
						msg = "û���κ�������Ϣ��";
					
					tell_object(me, msg +"\n");
				} else
					tell_object(me, "û���κ���Ϣ��\n");
			} else
					tell_object(me, "û���κ���Ϣ��\n");
		} else
		if (type == "-yes") {
			me->delete("sms/"+id);
			tell_object(me, "�����¼ɾ����ϡ�\n");
		}
		else if (type == "-clear") {
			msg = ZJOBLONG+"�����Ҫɾ����"+me->query("friends/"+id)[0]+"�������¼��\n";
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "ȷ��ɾ��:friends -jilu -yes "+ id;
			msg += ZJSEP"ȡ��:friends -jilu -qx "+ id;
			tell_object(me, msg +"\n");
			return 1;		
		}
	} else {
		if (arg == "-all") {
			if (list = me->query("sms")) 
			{
				if (sizeof(list) > 0)				
				{
					line = keys(list);
					for(i=0;i<sizeof(line);i++) 
					{
						list_a = list[line[i]];
						if (sizeof(list_a) > 0) 
						{
							linea = keys(list_a);
							for(j=0;j<sizeof(linea);j++) {
								if (list_a[linea[j]][1] == 1) {									
									str += sprintf("%s(δ��):%s", 
										HIG+(me->query("friends/"+line[i])[0])+NOR, "friends -jilu -wd " + line[i]);
									break;
								}
							}
						}
						
						if (str != "") {
							if (i<sizeof(line)-1)
								str += ZJSEP;
						}
					}	
					if (str !="") {
						msg = ZJOBLONG+"������Ϣ�б�\n";
						msg += ZJOBACTS2+ZJMENUF(3, 3, 9, 30);
						msg += str;
					} else
						msg = "û���κ�������Ϣ��";
					
					tell_object(me, msg +"\n");
				} else
					tell_object(me, "û���κ���Ϣ��\n");
			} else
					tell_object(me, "û���κ���Ϣ��\n");
				
			return 1;
		}
		id = arg;
		if (list = me->query("sms/"+id))
		{
			if (sizeof(list) > 0) {
				line = keys(list);
				line = sort_array(line, (: strcmp :));
				
				for(i=0;i<sizeof(line);i++) {
					GMT = to_int(line[i]);
					times = localtime(GMT);
					time = sprintf("%s-%s %s:%s:%s", (times[LT_MON] + 1)+"", times[LT_MDAY]+"", 
												times[LT_HOUR]+"", times[LT_MIN]+"", times[LT_SEC]+"");
					str += sprintf("%s(%s)"ZJBR, list[line[i]][0], time);
				}	
				msg = ZJOBLONG+("��"+me->query("friends/"+id)[0])+"�Ի�����Ϣ�б�("+sizeof(line)+"��)��"+ZJBR;
				msg += str+"\n";
				tell_object(me, msg +"\n");
			} else
				tell_object(me, "û���κ���ʷ��Ϣ��\n");
		} else
			tell_object(me, "û���κ���ʷ��Ϣ��\n");
	}
	
	return 1;
}

int do_apply(object me, string arg)
{
	mapping temp;
	string msg, str="";
	string *list;
	int i;
	
	if (temp = me->query("Friend/temp")) {
		if (sizeof(temp) < 1) {
			tell_object(me, "��û���յ��κ�������Ϣ��\n");
			return 1;
		}
		list = keys(temp);
		for(i=0;i<sizeof(list);i++) {
			str += sprintf("%s:%s", temp[list[i]][0], "friends -yesno "+ temp[list[i]][0] + " " + list[i]);
			if (i<sizeof(list)-1)
				str += ZJSEP;
		}
		
		msg = ZJOBLONG+"���������б�\n";
		msg += ZJOBACTS2+ZJMENUF(2, 2, 9, 30);
		msg += str;
		
		tell_object(me, msg +"\n");
	} else
		tell_object(me, "��û���յ��κ�������Ϣ��\n");
	return 1;
}